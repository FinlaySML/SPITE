#include "pch.h"
#include "SoundSystem_SoLoud.h"
#include <filesystem>

Spite::SoundSystem* Spite::sound = new Spite::SoundSystem_SoLoud();

namespace Spite {
    SoundSystem_SoLoud::SoundSystem_SoLoud() : idCount{0} {
    }

    int SoundSystem_SoLoud::Initialise() {
        auto result = engine.init();
        if (result != 0) {
            std::cout << std::format("Could not init SoLoud: {}", GetSoLoudErrorString(result)) << std::endl;
            return -1;
        }
        return 0;
    }

    int SoundSystem_SoLoud::Shutdown() {
        engine.deinit();
        return 0;
    }

    SoundSystem::SampleID SoundSystem_SoLoud::LoadSample(std::string file) {
        std::unique_ptr<SoLoud::Wav> sample{new SoLoud::Wav()};
        auto result = sample->load(file.c_str());
        if(result != 0) {
            std::cout << std::format("Could not load SoLoud sample: {}", GetSoLoudErrorString(result)) << std::endl;
            return {0};
        }
        idCount++;
        samples.insert(std::pair{idCount, std::move(sample)});
        return {idCount};
    }

    SoundSystem::StreamID SoundSystem_SoLoud::LoadStream(std::string file) {
        return StreamID();
    }

    void SoundSystem_SoLoud::Play(SampleID sampleId, float volume) {
        auto it = samples.find(sampleId.val);
        if(it == samples.end()) {
            std::cout << std::format("Could not find sample with ID {}", sampleId.val) << std::endl;
            return;
        }
        engine.play(*it->second, volume);
    }

    std::string SoundSystem_SoLoud::GetSoLoudErrorString(SoLoud::result errorCode) {
        switch(errorCode) {
        case SoLoud::SO_NO_ERROR: return "SO_NO_ERROR";
        case SoLoud::INVALID_PARAMETER: return "INVALID_PARAMETER";
        case SoLoud::FILE_NOT_FOUND: return "FILE_NOT_FOUND";
        case SoLoud::FILE_LOAD_FAILED: return "FILE_LOAD_FAILED";
        case SoLoud::DLL_NOT_FOUND: return "DLL_NOT_FOUND";
        case SoLoud::OUT_OF_MEMORY: return "OUT_OF_MEMORY";
        case SoLoud::NOT_IMPLEMENTED: return "NOT_IMPLEMENTED";
        }
        return "UNKNOWN_ERROR";
    }
}