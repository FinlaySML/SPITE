#pragma once
namespace Spite {
	struct SoundHandle {
		std::uint64_t underlying;
		SoundHandle Volume(float multiplier);
		SoundHandle Speed(float multiplier);
		SoundHandle Delay(float seconds);
		SoundHandle Play(bool isPlaying);
	};
}
