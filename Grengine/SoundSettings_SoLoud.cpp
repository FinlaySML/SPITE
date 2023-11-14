#include "pch.h"
#include "SoundSettings_SoLoud.h"
#include "SoundSystem_SoLoud.h"

Spite::SoundSettings_SoLoud::SoundSettings_SoLoud(SoLoud::handle handle) : handle{handle} {}

Spite::SoundSettings& Spite::SoundSettings_SoLoud::Volume(float multiplier) {
    auto& engine = ((Spite::SoundSystem_SoLoud*)Spite::sound)->GetEngine();
    engine.setVolume(handle, multiplier);
    return *this;
}

Spite::SoundSettings& Spite::SoundSettings_SoLoud::Speed(float multiplier) {
    auto& engine = ((Spite::SoundSystem_SoLoud*)Spite::sound)->GetEngine();
    engine.setRelativePlaySpeed(handle, multiplier);
    return *this;
}

Spite::SoundSettings& Spite::SoundSettings_SoLoud::Delay(float seconds) {
    auto& engine = ((Spite::SoundSystem_SoLoud*)Spite::sound)->GetEngine();
    engine.setDelaySamples(handle, seconds * engine.getSamplerate(handle));
    return *this;
}

Spite::SoundSettings& Spite::SoundSettings_SoLoud::Play(bool shouldPlay) {
    auto& engine = ((Spite::SoundSystem_SoLoud*)Spite::sound)->GetEngine();
    engine.setPause(handle, !shouldPlay);
    return *this;
}
