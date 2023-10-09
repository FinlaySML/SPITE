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
        int ProcessEvents() final;
        bool IsPressed(KeyValue) final;
        bool IsPressed(KeyLocation) final;
        int GetDownCount(KeyValue) final;
        int GetDownCount(KeyLocation) final;
        int GetUpCount(KeyValue) final;
        int GetUpCount(KeyLocation) final;
    protected:
        void UpdateStart();
        void UpdateEnd();
        void RenderStart();
        void RenderEnd();
    private:
        SDL_Scancode ConvertToSDLScancode(KeyLocation);
        SDL_Keycode ConvertToSDLKeycode(KeyValue);
        std::span<const uint8_t> keyboardState;
        std::unordered_map<Spite::KeyValue, SDL_Keycode> keyValueToKeycode;
        std::unordered_map<Spite::KeyLocation, SDL_Scancode> keyLocationToScancode;
        std::unordered_map<SDL_Keycode, Spite::KeyValue> keycodeToKeyValue;
        std::unordered_map<SDL_Scancode, Spite::KeyLocation> scancodeToKeyLocation;
        std::vector<uint8_t> keyDownUpdateCount;
        std::vector<uint8_t> keyDownRenderCount;
        std::vector<uint8_t> keyUpUpdateCount;
        std::vector<uint8_t> keyUpRenderCount;
        enum InputMode {
            UPDATE,
            RENDER
        }inputMode;
    };
}