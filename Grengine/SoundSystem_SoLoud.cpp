#include "pch.h"
#include "SoundSystem_SoLoud.h"
#include <filesystem>

Spite::SoundSystem* Spite::sound = new Spite::SoundSystem_SoLoud();

namespace Spite {
    SoundSystem_SoLoud::SoundSystem_SoLoud() {
    }

    int SoundSystem_SoLoud::Initialise() {
        auto result = engine.init();
        if (result != 0) {
            std::cout << std::format("Could not init SDL2 sound driver for SoLoud: {}", engine.getErrorString(result)) << std::endl;
            result = engine.init(1, SoLoud::Soloud::NULLDRIVER);
            if (result != 0) {
                std::cout << std::format("Could not init NULL sound driver for SoLoud: {}", engine.getErrorString(result)) << std::endl;
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
        auto it = streams.find(path);
        if (it != streams.end()) {
            return it->second.get();
        }
        auto result = streams.insert(std::pair{ path, new Spite::Stream_SoLoud(path) });
        return result.first->second.get();
    }

    Spite::SoundHandle SoundSystem_SoLoud::Play(Sample* sample, float volume) {
        auto handle = engine.play(((Spite::Sample_SoLoud*)sample)->wav, volume);
        return {handle};
    }

    Spite::SoundHandle SoundSystem_SoLoud::Play(Stream* sample, float volume) {
        auto handle = engine.play(((Spite::Stream_SoLoud*)sample)->wav, volume);
        return {handle};
    }

    void SoundSystem_SoLoud::SetVolume(SoundHandle handle, float multiplier) {
        engine.setVolume(handle.underlying, multiplier);
    }

    void SoundSystem_SoLoud::SetSpeed(SoundHandle handle, float multiplier) {
        engine.setRelativePlaySpeed(handle.underlying, multiplier);
    }

    void SoundSystem_SoLoud::SetDelay(SoundHandle handle, float seconds) {
        engine.setDelaySamples(handle.underlying, seconds * engine.getSamplerate(handle.underlying));
    }

    void SoundSystem_SoLoud::SetPlay(SoundHandle handle, bool isPlaying) {
        engine.setPause(handle.underlying, !isPlaying);
    }

    SoLoud::Soloud& SoundSystem_SoLoud::GetEngine() {
        return engine;
    }
}