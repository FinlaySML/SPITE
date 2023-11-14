#include "pch.h"
#include "ResourceSystem.h"

Spite::ResourceSystem* Spite::resource = new Spite::ResourceSystem();

int Spite::ResourceSystem::Initialise()
{
    return 0;
}

int Spite::ResourceSystem::Shutdown()
{
    return 0;
}

Spite::Image* Spite::ResourceSystem::GetImage(const std::filesystem::path& path)
{
    std::string pathString = path.string();
    auto it = images.find(pathString);
    if (it != images.end()) {
        return it->second.get();
    }
    //Texture
    stbi_set_flip_vertically_on_load(true);
    int x, y, n;
    unsigned char* pixelData = stbi_load(pathString.c_str(), &x, &y, &n, 4);
    if (pixelData == nullptr) {
        std::cout << std::format("Texture failed to load: {}", pathString) << std::endl;
        return nullptr;
    }
    auto result = images.insert({pathString, std::make_unique<Spite::Image>(pixelData, x, y)});
    stbi_image_free(pixelData);
    return result.first->second.get();
}
