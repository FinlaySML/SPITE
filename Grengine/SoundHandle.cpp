#include "pch.h"
#include "SoundHandle.h"
#include "SoundSystem.h"

Spite::SoundHandle Spite::SoundHandle::Volume(float multiplier) {
    Spite::sound->SetVolume(*this, multiplier);
    return *this;
}

Spite::SoundHandle Spite::SoundHandle::Speed(float multiplier) {
    Spite::sound->SetSpeed(*this, multiplier);
    return *this;
}

Spite::SoundHandle Spite::SoundHandle::Delay(float seconds) {
    Spite::sound->SetDelay(*this, seconds);
    return *this;
}

Spite::SoundHandle Spite::SoundHandle::Play(bool isPlaying) {
    Spite::sound->SetPlay(*this, isPlaying);
    return *this;
}
