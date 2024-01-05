#include "pch.h"
#include "PauseState.h"

bool Spite::IsPaused(PauseState state, bool isParentPaused) {
    bool thisPaused;
    switch (state) {
    case PauseState::NO: thisPaused = false; break;
    case PauseState::YES: thisPaused = true; break;
    default: thisPaused = isParentPaused; break;
    }
    return thisPaused;
}

const std::string& Spite::PauseToString(PauseState state) {
    switch (state) {
    case PauseState::NO: return "No";
    case PauseState::YES: return "Yes";
    default: return "Inherit";
    }
}

Spite::PauseState Spite::StringToPause(const std::string& str) {
    if (str == "No") {
        return PauseState::NO;
    }
    if (str == "Yes") {
        return PauseState::YES;
    }
    return PauseState::INHERIT;
}