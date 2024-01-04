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
        void Quit() final;
        bool IsPressed(KeyValue) final;
        bool IsPressed(KeyLocation) final;
        bool IsPressed(MouseButton) final;
        bool JustPressed(KeyValue) final;
        bool JustPressed(KeyLocation) final;
        bool JustPressed(MouseButton) final;
        bool JustReleased(KeyValue) final;
        bool JustReleased(KeyLocation) final;
        bool JustReleased(MouseButton) final;
        glm::ivec2 GetMousePosition() final;
    protected:
        bool HasQuit() final;
        void UpdateBegin() final;
        void UpdateEnd() final;
    private:
        SDL_Scancode ConvertToSDLScancode(KeyLocation);
        SDL_Keycode ConvertToSDLKeycode(KeyValue);
        uint8_t ConvertToSDLButton(MouseButton);
        std::span<const uint8_t> keyboardState;
        uint32_t mouseState;
        glm::ivec2 mousePosition;
        std::unordered_map<Spite::KeyValue, SDL_Keycode> keyValueToKeycode;
        std::unordered_map<Spite::KeyLocation, SDL_Scancode> keyLocationToScancode;
        std::unordered_map<SDL_Keycode, Spite::KeyValue> keycodeToKeyValue;
        std::unordered_map<SDL_Scancode, Spite::KeyLocation> scancodeToKeyLocation;
        std::unordered_map<Spite::MouseButton, uint8_t> mouseButtonToButton;
        std::unordered_map<uint8_t, Spite::MouseButton> buttonToMouseButton;
        std::vector<uint8_t> keyDownCount;
        std::vector<uint8_t> keyUpCount;
        std::array<uint8_t, 32> buttonDownCount;
        std::array<uint8_t, 32> buttonUpCount;
        bool quit;
    };
}