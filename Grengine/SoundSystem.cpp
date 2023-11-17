#include "pch.h"
#include "SoundSystem.h"

Spite::SoundHandle Spite::SoundSystem::LoadSampleAndPlay(const std::filesystem::path& path, float volume) {
    return Play(LoadSample(path), volume);
}

Spite::SoundHandle Spite::SoundSystem::LoadStreamAndPlay(const std::filesystem::path& path, float volume) {
    return Play(LoadStream(path), volume);
}
