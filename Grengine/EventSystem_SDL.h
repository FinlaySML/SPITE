#pragma once
#include "EventSystem.h"

namespace Spite {
    /// <summary>
    /// SDL Implementation to our EventSystem interface
    /// Handles the SDL message loop and dispatches
    /// the messages
    /// </summary>
    class EventSystem_SDL :
        public EventSystem
    {
    public:
        int Initialise();
        int Shutdown();
        void ProcessEvents() final;
        void Quit() final;
        bool IsPressed(KeyValue) final;
        bool IsPressed(KeyLocation) final;
        bool JustPressed(KeyValue) final;
        bool JustPressed(KeyLocation) final;
        bool JustReleased(KeyValue) final;
        bool JustReleased(KeyLocation) final;
    protected:
        bool HasQuit();
        void UpdateEnd();
    private:
        SDL_Scancode ConvertToSDLScancode(KeyLocation);
        SDL_Keycode ConvertToSDLKeycode(KeyValue);
        std::span<const uint8_t> keyboardState;
        std::unordered_map<Spite::KeyValue, SDL_Keycode> keyValueToKeycode;
        std::unordered_map<Spite::KeyLocation, SDL_Scancode> keyLocationToScancode;
        std::unordered_map<SDL_Keycode, Spite::KeyValue> keycodeToKeyValue;
        std::unordered_map<SDL_Scancode, Spite::KeyLocation> scancodeToKeyLocation;
        std::vector<uint8_t> keyDownCount;
        std::vector<uint8_t> keyUpCount;
        bool quit;
    };
}