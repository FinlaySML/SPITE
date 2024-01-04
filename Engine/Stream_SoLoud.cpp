#include "pch.h"
#include "Stream_SoLoud.h"
#include "SoundSystem_SoLoud.h"

Spite::Stream_SoLoud::Stream_SoLoud(const std::filesystem::path& path) {
    std::string pathString = "Assets/" + path.string();
    auto result = wav.load(pathString.c_str());
    if (result != 0) {
        std::cout << std::format("Could not load SoLoud sample: {}", ((Spite::SoundSystem_SoLoud*)Spite::sound)->GetEngine().getErrorString(result)) << std::endl;
    }
}
