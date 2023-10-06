#include "pch.h"
#include "Texture.h"
namespace Spite {
	Texture::Texture(const std::string& file) : loaded(false) {
        LoadFromFile(file);
	}
    Texture::Texture() : loaded(false) {}
    void Texture::LoadFromFile(const std::string& file) {
        if (IsLoaded()) {
            std::cout << "Can't load texture again, texture has already been loaded!" << std::endl;
            return;
        }
        //Texture
        stbi_set_flip_vertically_on_load(GetShouldFlipTextures());
        int x, y, n;
        stbi_uc* pixelData = stbi_load(file.c_str(), &x, &y, &n, 4);
        if (pixelData == nullptr) {
            std::cout << std::format("Texture failed to load: {}", file) << std::endl;
            return;
        }
        SendToGPU(pixelData, x, y);
        stbi_image_free(pixelData);
        loaded = true;
    }
    Texture::~Texture() {
    }
    bool Texture::IsLoaded() {
        return loaded;
    }
    void Texture::SetLoaded(bool l) {
        loaded = l;
    }
}