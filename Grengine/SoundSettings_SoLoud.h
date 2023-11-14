#pragma once
#include "SoundSettings.h"
#include "soloud.h"

namespace Spite {
	class SoundSettings_SoLoud : public SoundSettings {
	public:
		SoundSettings_SoLoud(SoLoud::handle handle);
		SoLoud::handle handle;
		SoundSettings& Volume(float value) override;
		SoundSettings& Speed(float value) override;
		SoundSettings& Delay(float value) override;
		SoundSettings& Play(bool value) override;
	};
}
