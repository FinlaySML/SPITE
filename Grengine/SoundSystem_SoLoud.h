#pragma once
#include "SoundSystem.h"
#include "soloud.h"
#include "soloud_wav.h"

namespace Spite {
	class SoundSystem_SoLoud : public SoundSystem {
	public:
		SoundSystem_SoLoud();
		int Initialise() final;
		int Shutdown() final;
		SampleID LoadSample(std::string file) final;
		StreamID LoadStream(std::string file) final;
		void Play(SampleID sampleId) final;
	private:
		std::string GetSoLoudErrorString(SoLoud::result errorCode);
		std::unordered_map<unsigned int, std::unique_ptr<SoLoud::Wav>> samples;
		SoLoud::Soloud engine;
		unsigned int idCount;
	};
}