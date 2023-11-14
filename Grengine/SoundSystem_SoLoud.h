#pragma once
#include "SoundSystem.h"
#include "soloud.h"
#include "soloud_wav.h"
#include "Sample_SoLoud.h"
#include "Stream_SoLoud.h"
#include "SoundSettings_SoLoud.h"

namespace Spite {
	class SoundSystem_SoLoud : public SoundSystem {
	public:
		SoundSystem_SoLoud();
		int Initialise() final;
		void Update() final;
		int Shutdown() final;
		Sample* LoadSample(const std::filesystem::path& path) final;
		Stream* LoadStream(const std::filesystem::path& path) final;
		SoundSettings* Play(Sample* sample, float volume = 1.0f) final;
		SoundSettings* Play(Stream* sample, float volume = 1.0f) final;
		SoLoud::Soloud& GetEngine();
	private:
		std::unordered_map<std::filesystem::path, std::unique_ptr<Sample_SoLoud>> samples;
		std::unordered_map<std::filesystem::path, std::unique_ptr<Stream_SoLoud>> streams;
		std::vector<std::unique_ptr<SoundSettings_SoLoud>> handles;
		SoLoud::Soloud engine;
	};
}