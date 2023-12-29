#pragma once
#include "pch.h"
#include "Subsystem.h"
#include "Sample.h"
#include "Stream.h"
#include "SoundHandle.h"

namespace Spite {
    class SoundSystem : public Subsystem {
    public:
        virtual Sample* LoadSample(const std::filesystem::path& path) = 0;
        virtual Stream* LoadStream(const std::filesystem::path& path) = 0;
        virtual SoundHandle Play(Sample* sample, float volume = 1.0f) = 0;
        virtual SoundHandle Play(Stream* sample, float volume = 1.0f) = 0;
        SoundHandle LoadSampleAndPlay(const std::filesystem::path& path, float volume = 1.0f);
        SoundHandle LoadStreamAndPlay(const std::filesystem::path& path, float volume = 1.0f);
        virtual void SetVolume(SoundHandle handle, float multiplier) = 0;
        virtual void SetSpeed(SoundHandle handle, float multiplier) = 0;
        virtual void SetDelay(SoundHandle handle, float seconds) = 0;
        virtual void SetPlay(SoundHandle handle, bool isPlaying) = 0;
        virtual void SetLoop(SoundHandle handle, bool isLooping) = 0;
    };
    extern SoundSystem* sound;
}