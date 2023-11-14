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
            std::cout << std::format("Could not init SDL2 sound driver for SoLoud: {}", GetSoLoudErrorString(result)) << std::endl;
            result = engine.init(1, SoLoud::Soloud::NULLDRIVER);
            if (result != 0) {
                std::cout << std::format("Could not init NULL sound driver for SoLoud: {}", GetSoLoudErrorString(result)) << std::endl;
                return -1;
            }
            std::cout << "No audio device could be found" << std::endl;
            return 0;
        }
        return 0;
    }

    int SoundSystem_SoLoud::Shutdown() {
        engine.deinit();
        return 0;
    }

    Sample* SoundSystem_SoLoud::LoadSample(const std::filesystem::path& path)
    {
        auto it = samples.find(path);
        if (it != samples.end()) {
            return it->second.get();
        }
        auto result = samples.insert(std::pair{ path, new Spite::Sample_SoLoud(path)});
        return result.first->second.get();
    }

    Stream* SoundSystem_SoLoud::LoadStream(const std::filesystem::path& path)
    {
        return nullptr;
    }

    void SoundSystem_SoLoud::Play(Sample* sample, float volume) {
        engine.play(((Spite::Sample_SoLoud*)sample)->wav, volume);
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