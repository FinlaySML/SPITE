#include "pch.h"
#include "Texture_GL.h"
#include "TextureRegion.h"

unsigned int CreateGLTexture(unsigned char* pixelData, glm::ivec2 dimensions) {
    unsigned int tex{0};
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, dimensions.x, dimensions.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);
    glBindTexture(GL_TEXTURE_2D, 0);
    return tex;
}

Spite::Texture_GL::Texture_GL() : loaded{ false }, dimensions{ 0,0 }, handle{0} {}

void Spite::Texture_GL::LoadFromFile(const std::string& file) {
    if (IsLoaded()) {
        std::cout << "Can't load texture again, texture has already been loaded!" << std::endl;
        return;
    }
    auto filePath{"Assets/"+file};
    //Texture
    stbi_set_flip_vertically_on_load(true);
    int x, y, n;
    unsigned char* pixelData = stbi_load(filePath.c_str(), &x, &y, &n, 4);
    if (pixelData == nullptr) {
        std::cout << std::format("Texture failed to load: {}", file) << std::endl;
        return;
    }
    handle = CreateGLTexture(pixelData, {x, y});
    stbi_image_free(pixelData);
    dimensions = { x, y };
    loaded = true;
    path = file;
}

void Spite::Texture_GL::LoadFromData(std::span<unsigned char> data, glm::ivec2 dataDimensions) {
    if (IsLoaded()) {
        std::cout << "Texture failed to load, texture has already been loaded!" << std::endl;
        return;
    }
    if(dataDimensions.x <= 0 || dataDimensions.y <= 0) {
        std::cout << std::format("Texture failed to load, dimensions must be greater than 0 (x={},y={})", dataDimensions.x, dataDimensions.y) << std::endl;
        return;
    }
    if (data.size() != dataDimensions.x * dataDimensions.y * 4) {
        std::cout << std::format("Texture failed to load, there is {} bytes of texture data but {} was needed (x={},y={})", data.size(), dataDimensions.x * dataDimensions.y * 4, dataDimensions.x, dataDimensions.y) << std::endl;
        return;
    }
    handle = CreateGLTexture(data.data(), dataDimensions);
    dimensions = dataDimensions;
    loaded = true;
}

void Spite::Texture_GL::Resize(glm::ivec2 newDimensions) {
    if(!IsLoaded()) {
        std::cout << "Cannot resize a texture before it has been loaded!" << std::endl;
        return;
    }
    if(newDimensions.x < dimensions.x || newDimensions.y < dimensions.y) {
        std::cout << std::format("Cannot resize a texture to make it bigger, {} to {} is invalid", glm::to_string(dimensions), glm::to_string(newDimensions)) << std::endl;
        return;
    }
    std::vector<unsigned char> data(newDimensions.x * newDimensions.y * 4, 0xff);
    unsigned int oldHandle = handle;
    glm::ivec2 oldDimensions = dimensions;
    handle = CreateGLTexture(data.data(), newDimensions);
    dimensions = newDimensions;
    glCopyImageSubData(oldHandle, GL_TEXTURE_2D, 0, 0, 0, 0, handle, GL_TEXTURE_2D, 0, 0, 0, 0, oldDimensions.x, oldDimensions.y, 1);
    glDeleteTextures(1, &oldHandle);
}

void Spite::Texture_GL::Blit(const TextureRegion& source, glm::ivec2 offset) {
    if (!IsLoaded()) {
        std::cout << "Cannot blit to a texture before it has been loaded!" << std::endl;
        return;
    }
    if(!source.texture->IsLoaded()) {
        std::cout << "Cannot blit from a texture before it has been loaded!" << std::endl;
        return;
    }
    glCopyImageSubData(((Texture_GL*)source.texture.get())->handle, GL_TEXTURE_2D, 0, source.origin.x, source.origin.y, 0, handle, GL_TEXTURE_2D, 0, offset.x, offset.y, 0, source.dimensions.x, source.dimensions.y, 1);
}

bool Spite::Texture_GL::IsLoaded() {
    return loaded;
}

glm::ivec2 Spite::Texture_GL::GetDimensions() {
    return dimensions;
}

const std::optional<std::string>& Spite::Texture_GL::Path() {
    return path;
}

Spite::Texture_GL::~Texture_GL() {
    if(IsLoaded()) {
        glDeleteTextures(1, &handle);
    }
}

unsigned int Spite::Texture_GL::GetHandle() {
    if(!IsLoaded()) {
        std::cout << "You should not use a texture that isn't loaded!" << std::endl;
    }
    return handle;
}