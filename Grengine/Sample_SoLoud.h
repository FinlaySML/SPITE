#pragma once
#include "Sample.h"
#include "soloud_wav.h"

namespace Spite {
    class Sample_SoLoud :public Sample
    {
    public:
        Sample_SoLoud(const std::filesystem::path& path);
        SoLoud::Wav wav;
    };
}

