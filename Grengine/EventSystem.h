#pragma once
#include "Subsystem.h"
namespace Spite {
    /// <summary>
    /// Interface base class to our event system
    /// </summary>
    class EventSystem :
        public Subsystem
    {
    public:
        virtual int ProcessEvents() = 0;
    };

    extern EventSystem* event;
}
