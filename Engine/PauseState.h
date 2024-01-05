#pragma once
#include <string>
namespace Spite {
    enum class PauseState {
	    NO,
	    YES,
	    INHERIT,
    };

    bool IsPaused(PauseState state, bool isParentPaused);
    const std::string& PauseToString(PauseState state);
    PauseState StringToPause(const std::string& str);
}