#pragma once
#include "pch.h"
#include "Subsystem.h"
#include "Sample.h"
#include "Stream.h"
namespace Spite {
    class SoundSystem : public Subsystem {
    public:
        virtual Sample* LoadSample(const std::filesystem::path& path) = 0;
        virtual Stream* LoadStream(const std::filesystem::path& path) = 0;
        virtual SoundSettings* Play(Sample* sample) = 0;
        virtual SoundSettings* Play(Stream* sample) = 0;
    };
    extern SoundSystem* sound;
}