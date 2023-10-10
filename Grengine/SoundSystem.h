#pragma once
#include "pch.h"
#include "Subsystem.h"
namespace Spite {
    class SoundSystem : public Subsystem {
    public:
        struct SampleID {
            unsigned int val = -1;
        };
        struct StreamID {
            unsigned int val = -1;
        };
        virtual SampleID LoadSample(std::string file) = 0;
        virtual StreamID LoadStream(std::string file) = 0;
        virtual void Play(SampleID sampleId, float volume=1.0f) = 0;
    };

    extern SoundSystem* sound;
}