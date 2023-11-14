#pragma once
namespace Spite {
	class SoundSettings {
	public:
		virtual SoundSettings& Volume(float multiplier) = 0;
		virtual SoundSettings& Speed(float multiplier) = 0;
		virtual SoundSettings& Delay(float seconds) = 0;
		virtual SoundSettings& Play(bool isPlaying) = 0;
	};
}
