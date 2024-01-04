#pragma once
#include "Stream.h"
#include "soloud_wavstream.h"

namespace Spite {
	class Stream_SoLoud : public Stream {
	public:
		Stream_SoLoud(const std::filesystem::path& path);
		SoLoud::WavStream wav;
	};
}