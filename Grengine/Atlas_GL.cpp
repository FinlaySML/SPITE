#include "pch.h"
#include "Atlas_GL.h"

unsigned int maxAtlasSize{4096};

Spite::Atlas_GL::Atlas_GL() : atlasSize{32} {
	std::vector<unsigned char> data(atlasSize * atlasSize *4, 0xff);
	texture.LoadFromData(data, atlasSize, atlasSize);
}

Spite::Atlas_GL::~Atlas_GL() {}

Spite::TextureRegion Spite::Atlas_GL::ConvertRegion(const TextureRegion& region) {
    glm::ivec2 texDim = region.texture->GetDimensions();
    //Get offset in atlas
    glm::ivec2 offset{ 0, 0 };
    auto it = atlasOffsets.find(region.texture);
    if (it != atlasOffsets.end()) {
        offset = it->second;
    } else {
        auto opt = FindFreeAtlasRegion(texDim);
        while (!opt) {
            if(atlasSize == maxAtlasSize) {
                std::cout << "Max atlas size reached, can't make room" << std::endl;
                return { &texture, region.origin, region.dimensions };
            }
            //Could not find free space in the atlas, make it bigger
            atlasSize *= 2;
            texture.Resize(glm::ivec2{ atlasSize, atlasSize });
            //Don't need to check, as long as there are no bugs it should be able to find a free region big enough
            opt = FindFreeAtlasRegion(texDim);
        }
        offset = opt.value();
        texture.Blit({region.texture}, offset);
        atlasOffsets.insert({ region.texture, offset });
    }
	return { &texture, region.origin + offset, region.dimensions };
}

Spite::Texture* Spite::Atlas_GL::GetTexture() {
	return &texture;
}

unsigned int Spite::Atlas_GL::GetTextureGL() {
    return texture.GetHandle();
}

std::optional<glm::vec2> Spite::Atlas_GL::FindFreeAtlasRegion(glm::vec2 dimensions) {
    if (dimensions.x > atlasSize || dimensions.y > atlasSize) {
        return {};
    }
    glm::ivec2 offset{ 1,0 };
    bool collision;
    do {
        collision = false;
        for (auto& pair : atlasOffsets) {
            auto off{ pair.second };
            auto dim{ pair.first->GetDimensions() };
            if (offset.x < off.x + dim.x && offset.x + dimensions.x > off.x &&
                offset.y < off.y + dim.y && offset.y + dimensions.y > off.y) {
                collision = true;
                offset.x = off.x + dim.x;
                if (offset.x + dimensions.x > atlasSize) {
                    offset.x = 0;
                    offset.y++;
                    if (offset.y + dimensions.y > atlasSize) {
                        return {};
                    }
                    break;
                }
            }
        }
    } while (collision);
    return offset;
}