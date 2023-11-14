#pragma once
#include "pch.h"
#include "Subsystem.h"
#include "Sample.h"
#include "Stream.h"
#include "SoundSettings.h"

namespace Spite {
    class SoundSystem : public Subsystem {
    public:
        virtual void Update() = 0;
        virtual Sample* LoadSample(const std::filesystem::path& path) = 0;
        virtual Stream* LoadStream(const std::filesystem::path& path) = 0;
        virtual SoundSettings* Play(Sample* sample, float volume = 1.0f) = 0;
        virtual SoundSettings* Play(Stream* sample, float volume = 1.0f) = 0;
        SoundSettings* LoadSampleAndPlay(const std::filesystem::path& path, float volume = 1.0f);
        SoundSettings* LoadStreamAndPlay(const std::filesystem::path& path, float volume = 1.0f);
    };
    extern SoundSystem* sound;
}