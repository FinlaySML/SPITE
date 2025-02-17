#pragma once
#include "SoundSystem.h"
#include "soloud.h"
#include "soloud_wav.h"
#include "Sample_SoLoud.h"
#include "Stream_SoLoud.h"

namespace Spite {
	class SoundSystem_SoLoud : public SoundSystem {
	public:
		SoundSystem_SoLoud();
		int Initialise() final;
		int Shutdown() final;
		Sample* LoadSample(const std::filesystem::path& path) final;
		Stream* LoadStream(const std::filesystem::path& path) final;
		SoundHandle Play(Sample* sample, float volume = 1.0f) final;
		SoundHandle Play(Stream* sample, float volume = 1.0f) final;
		void SetVolume(SoundHandle handle, float multiplier) final;
		void SetSpeed(SoundHandle handle, float multiplier) final;
		void SetDelay(SoundHandle handle, float seconds) final;
		void SetPlay(SoundHandle handle, bool isPlaying) final;
		void SetLoop(SoundHandle handle, bool isLooping) final;
		void SetSeek(SoundHandle handle, float seconds) final;
		bool IsValid(SoundHandle handle) final;
		void SetGlobalVolume(float fraction) final;
		void PrintDebugInfo() final;
		SoLoud::Soloud& GetEngine();
	private:
		std::unordered_map<std::filesystem::path, std::unique_ptr<Sample_SoLoud>> samples;
		std::unordered_map<std::filesystem::path, std::unique_ptr<Stream_SoLoud>> streams;
		SoLoud::Soloud engine;
	};
}