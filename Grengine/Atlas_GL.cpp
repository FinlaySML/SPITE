#include "pch.h"
#include "Atlas_GL.h"

const unsigned int MAX_ATLAS_SIZE{4096};

Spite::Atlas_GL::Atlas_GL() : atlasSize{32}, texture{std::make_shared<Spite::Texture_GL>()} {
	std::vector<unsigned char> data(atlasSize * atlasSize * 4, 0xff);
	texture->LoadFromData(data, {atlasSize, atlasSize});
}

Spite::Atlas_GL::~Atlas_GL() {}

Spite::TextureRegion Spite::Atlas_GL::ConvertRegion(const TextureRegion& region) {
    glm::ivec2 texDim = region.texture->GetDimensions();
    //Get offset in atlas
    glm::ivec2 offset{ 0, 0 };
    auto it = atlassed.find(region.texture.get());
    if (it != atlassed.end()) {
        //The texture is already in the atlas
        offset = it->second.offset;
    } else {
        //Add the texture to the atlas
        auto opt = FindFreeAtlasRegion(texDim);
        //While there is no free spot, repeatedly double the atlas size
        while (!opt) {
            //Could not find free space in the atlas, make it bigger
            auto newAtlasSize{atlasSize * 2};
            if(newAtlasSize > MAX_ATLAS_SIZE) {
                std::cout << "Max atlas size reached, can't make room" << std::endl;
                return { texture, region.origin, region.dimensions };
            }
            texture->Resize(glm::ivec2{ newAtlasSize, newAtlasSize });
            atlasSize = newAtlasSize;
            //Retry to see if the atlas is big enough this time
            opt = FindFreeAtlasRegion(texDim);
        }
        offset = opt.value();
        texture->Blit({region.texture}, offset);
        atlassed.insert({ region.texture.get(), TextureInAtlas{offset, region.texture}});
    }
	return { texture, region.origin + offset, region.dimensions };
}

unsigned int Spite::Atlas_GL::GetTextureGL() {
    return texture->GetHandle();
}

//Algorithm scans along the x and then moves up the y line by line to search for an empty region of the given dimensions
std::optional<glm::vec2> Spite::Atlas_GL::FindFreeAtlasRegion(glm::vec2 dimensions) {

    //There is no point in looking for an empty atlas region if there is no possible way of it fitting
    if (dimensions.x > atlasSize || dimensions.y > atlasSize) {
        return {};
    }
    //Skip the first pixel so there is a texture region to use for textureless/solid colour rendering
    glm::ivec2 offset{ 1,0 };
    if (offset.x + dimensions.x > atlasSize) {
        offset.x = 0;
        offset.y++;
        if (offset.y + dimensions.y > atlasSize) {
            //Since we are now outside the atlas bounds, return that there is no free region
            return {};
        }
    }
    bool collision;
    do {
        collision = false;
        std::vector<Texture*> expired;
        for (auto& pair : atlassed) {
            //Check that the texture still exists (if not, delete the atlassed region later)
            if(pair.second.tex.expired()) {
                expired.push_back(pair.first);
                continue;
            }
            //Get the rectangle of the occupied atlas region
            auto off{ pair.second.offset };
            auto dim{ pair.second.tex.lock()->GetDimensions() };
            if (offset.x < off.x + dim.x && offset.x + dimensions.x > off.x &&
                offset.y < off.y + dim.y && offset.y + dimensions.y > off.y) {
                //The proposed region overlaps with an occupied one
                collision = true;
                //Move along offset to make a new proposed region
                offset.x = off.x + dim.x;
                if (offset.x + dimensions.x > atlasSize) {
                    offset.x = 0;
                    offset.y++;
                    if (offset.y + dimensions.y > atlasSize) {
                        //Since we are now outside the atlas bounds, return that there is no free region
                        return {};
                    }
                    break;
                }
            }
        }
        //Delete any atlassed texture regions that are expired
        for (Texture* e : expired) {
            atlassed.erase(e);
        }
        
    } while (collision);
    return offset;
}