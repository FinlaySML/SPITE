#include "pch.h"
#include "SoundSystem.h"

Spite::SoundSettings* Spite::SoundSystem::LoadSampleAndPlay(const std::filesystem::path& path, float volume) {
    return Play(LoadSample(path), volume);
}

Spite::SoundSettings* Spite::SoundSystem::LoadStreamAndPlay(const std::filesystem::path& path, float volume) {
    return Play(LoadStream(path), volume);
}
