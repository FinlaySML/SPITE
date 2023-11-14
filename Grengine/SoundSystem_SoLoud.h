#pragma once
#include "SoundSystem.h"
#include "soloud.h"
#include "soloud_wav.h"
#include "Sample_SoLoud.h"
namespace Spite {
	class SoundSystem_SoLoud : public SoundSystem {
	public:
		SoundSystem_SoLoud();
		int Initialise() final;
		int Shutdown() final;
		Sample* LoadSample(const std::filesystem::path& path) final;
		Stream* LoadStream(const std::filesystem::path& path) final;
		void Play(Sample* sampleId, float volume=1.0f) final;
		static std::string GetSoLoudErrorString(SoLoud::result errorCode);
	private:
		std::unordered_map<std::filesystem::path, std::unique_ptr<Sample_SoLoud>> samples;
		SoLoud::Soloud engine;
	};
}