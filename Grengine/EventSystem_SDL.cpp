#include "pch.h"
#include "EventSystem_SDL.h"

#include "RenderSystem.h"

//We're globally instancing our subsystems!
//But maybe you think Globals are bad
//There might be other ways to approach this.
#ifdef RENDERSYSTEM_SDL
    Spite::EventSystem_SDL grEventSystemSDL;
    Spite::EventSystem* Spite::event = &grEventSystemSDL;
#endif

int Spite::EventSystem_SDL::Initialise()
{
    int numkeys = 0;
    const uint8_t* keys = SDL_GetKeyboardState(&numkeys);
    keyboardState = std::span<const uint8_t>{keys, (size_t)numkeys};
    keyDownUpdateCount.resize(numkeys);
    keyDownRenderCount.resize(numkeys);
    keyUpUpdateCount.resize(numkeys);
    keyUpRenderCount.resize(numkeys);
    //KeyValues
    keyValueToKeycode.insert({ Spite::KeyValue::KV_UNKNOWN, SDLK_UNKNOWN });
    keyValueToKeycode.insert({ Spite::KeyValue::KV_RETURN,SDLK_RETURN});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_ESCAPE,SDLK_ESCAPE});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_BACKSPACE,SDLK_BACKSPACE});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_TAB,SDLK_TAB});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_SPACE,SDLK_SPACE});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_EXCLAIM,SDLK_EXCLAIM});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_QUOTEDBL,SDLK_QUOTEDBL});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_HASH,SDLK_HASH});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_PERCENT,SDLK_PERCENT});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_DOLLAR,SDLK_DOLLAR});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_AMPERSAND,SDLK_AMPERSAND});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_QUOTE,SDLK_QUOTE});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_LEFTPAREN,SDLK_LEFTPAREN});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_RIGHTPAREN,SDLK_RIGHTPAREN});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_ASTERISK,SDLK_ASTERISK});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_PLUS,SDLK_PLUS});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_COMMA,SDLK_COMMA});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_MINUS,SDLK_MINUS});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_PERIOD,SDLK_PERIOD});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_SLASH,SDLK_SLASH});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_0,SDLK_0});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_1,SDLK_1});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_2,SDLK_2});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_3,SDLK_3});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_4,SDLK_4});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_5,SDLK_5});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_6,SDLK_6});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_7,SDLK_7});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_8,SDLK_8});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_9,SDLK_9});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_COLON,SDLK_COLON});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_SEMICOLON,SDLK_SEMICOLON});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_LESS,SDLK_LESS});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_EQUALS,SDLK_EQUALS});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_GREATER,SDLK_GREATER});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_QUESTION,SDLK_QUESTION});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_AT,SDLK_AT});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_LEFTBRACKET,SDLK_LEFTBRACKET});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_BACKSLASH,SDLK_BACKSLASH});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_RIGHTBRACKET,SDLK_RIGHTBRACKET});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_CARET,SDLK_CARET});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_UNDERSCORE,SDLK_UNDERSCORE});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_BACKQUOTE,SDLK_BACKQUOTE});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_A,SDLK_a});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_B,SDLK_b});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_C,SDLK_c});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_D,SDLK_d});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_E,SDLK_e});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_F,SDLK_f});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_G,SDLK_g});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_H,SDLK_h});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_I,SDLK_i});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_J,SDLK_j});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_K,SDLK_k});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_L,SDLK_l});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_M,SDLK_m});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_N,SDLK_n});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_O,SDLK_o});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_P,SDLK_p});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_Q,SDLK_q});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_R,SDLK_r});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_S,SDLK_s});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_T,SDLK_t});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_U,SDLK_u});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_V,SDLK_v});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_W,SDLK_w});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_X,SDLK_x});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_Y,SDLK_y});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_Z,SDLK_z});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_CAPSLOCK,SDLK_CAPSLOCK});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_F1,SDLK_F1});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_F2,SDLK_F2});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_F3,SDLK_F3});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_F4,SDLK_F4});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_F5,SDLK_F5});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_F6,SDLK_F6});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_F7,SDLK_F7});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_F8,SDLK_F8});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_F9,SDLK_F9});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_F10,SDLK_F10});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_F11,SDLK_F11});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_F12,SDLK_F12});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_PRINTSCREEN,SDLK_PRINTSCREEN});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_SCROLLLOCK,SDLK_SCROLLLOCK});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_PAUSE,SDLK_PAUSE});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_INSERT,SDLK_INSERT});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_HOME,SDLK_HOME});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_PAGEUP,SDLK_PAGEUP});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_DELETE,SDLK_DELETE});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_END,SDLK_END});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_PAGEDOWN,SDLK_PAGEDOWN});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_RIGHT,SDLK_RIGHT});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_LEFT,SDLK_LEFT});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_DOWN,SDLK_DOWN});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_UP,SDLK_UP});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_NUMLOCKCLEAR,SDLK_NUMLOCKCLEAR});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_DIVIDE,SDLK_KP_DIVIDE});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_MULTIPLY,SDLK_KP_MULTIPLY});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_MINUS,SDLK_KP_MINUS});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_PLUS,SDLK_KP_PLUS});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_ENTER,SDLK_KP_ENTER});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_1,SDLK_KP_1});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_2,SDLK_KP_2});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_3,SDLK_KP_3});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_4,SDLK_KP_4});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_5,SDLK_KP_5});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_6,SDLK_KP_6});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_7,SDLK_KP_7});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_8,SDLK_KP_8});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_9,SDLK_KP_9});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_0,SDLK_KP_0});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_PERIOD,SDLK_KP_PERIOD});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_APPLICATION,SDLK_APPLICATION});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_POWER,SDLK_POWER});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_EQUALS,SDLK_KP_EQUALS});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_F13,SDLK_F13});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_F14,SDLK_F14});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_F15,SDLK_F15});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_F16,SDLK_F16});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_F17,SDLK_F17});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_F18,SDLK_F18});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_F19,SDLK_F19});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_F20,SDLK_F20});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_F21,SDLK_F21});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_F22,SDLK_F22});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_F23,SDLK_F23});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_F24,SDLK_F24});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_EXECUTE,SDLK_EXECUTE});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_HELP,SDLK_HELP});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_MENU,SDLK_MENU});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_SELECT,SDLK_SELECT});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_STOP,SDLK_STOP});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_AGAIN,SDLK_AGAIN});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_UNDO,SDLK_UNDO});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_CUT,SDLK_CUT});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_COPY,SDLK_COPY});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_PASTE,SDLK_PASTE});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_FIND,SDLK_FIND});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_MUTE,SDLK_MUTE});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_VOLUMEUP,SDLK_VOLUMEUP});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_VOLUMEDOWN,SDLK_VOLUMEDOWN});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_COMMA,SDLK_KP_COMMA});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_EQUALSAS400,SDLK_KP_EQUALSAS400});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_ALTERASE,SDLK_ALTERASE});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_SYSREQ,SDLK_SYSREQ});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_CANCEL,SDLK_CANCEL});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_CLEAR,SDLK_CLEAR});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_PRIOR,SDLK_PRIOR});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_RETURN2,SDLK_RETURN2});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_SEPARATOR,SDLK_SEPARATOR});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_OUT,SDLK_OUT});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_OPER,SDLK_OPER});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_CLEARAGAIN,SDLK_CLEARAGAIN});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_CRSEL,SDLK_CRSEL});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_EXSEL,SDLK_EXSEL});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_00,SDLK_KP_00});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_000,SDLK_KP_000});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_THOUSANDSSEPARATOR,SDLK_THOUSANDSSEPARATOR});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_DECIMALSEPARATOR,SDLK_DECIMALSEPARATOR});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_CURRENCYUNIT,SDLK_CURRENCYUNIT});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_CURRENCYSUBUNIT,SDLK_CURRENCYSUBUNIT});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_LEFTPAREN,SDLK_KP_LEFTPAREN});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_RIGHTPAREN,SDLK_KP_RIGHTPAREN});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_LEFTBRACE,SDLK_KP_LEFTBRACE});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_RIGHTBRACE,SDLK_KP_RIGHTBRACE});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_TAB,SDLK_KP_TAB});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_BACKSPACE,SDLK_KP_BACKSPACE});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_A,SDLK_KP_A});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_B,SDLK_KP_B});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_C,SDLK_KP_C});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_D,SDLK_KP_D});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_E,SDLK_KP_E});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_F,SDLK_KP_F});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_XOR,SDLK_KP_XOR});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_POWER,SDLK_KP_POWER});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_PERCENT,SDLK_KP_PERCENT});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_LESS,SDLK_KP_LESS});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_GREATER,SDLK_KP_GREATER});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_AMPERSAND,SDLK_KP_AMPERSAND});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_DBLAMPERSAND,SDLK_KP_DBLAMPERSAND});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_VERTICALBAR,SDLK_KP_VERTICALBAR});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_DBLVERTICALBAR,SDLK_KP_DBLVERTICALBAR});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_COLON,SDLK_KP_COLON});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_HASH,SDLK_KP_HASH});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_SPACE,SDLK_KP_SPACE});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_AT,SDLK_KP_AT});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_EXCLAM,SDLK_KP_EXCLAM});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_MEMSTORE,SDLK_KP_MEMSTORE});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_MEMRECALL,SDLK_KP_MEMRECALL});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_MEMCLEAR,SDLK_KP_MEMCLEAR});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_MEMADD,SDLK_KP_MEMADD});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_MEMSUBTRACT,SDLK_KP_MEMSUBTRACT});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_MEMMULTIPLY,SDLK_KP_MEMMULTIPLY});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_MEMDIVIDE,SDLK_KP_MEMDIVIDE});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_PLUSMINUS,SDLK_KP_PLUSMINUS});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_CLEAR,SDLK_KP_CLEAR});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_CLEARENTRY,SDLK_KP_CLEARENTRY});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_BINARY,SDLK_KP_BINARY});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_OCTAL,SDLK_KP_OCTAL});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_DECIMAL,SDLK_KP_DECIMAL});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KP_HEXADECIMAL,SDLK_KP_HEXADECIMAL});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_LCTRL,SDLK_LCTRL});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_LSHIFT,SDLK_LSHIFT});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_LALT,SDLK_LALT});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_LGUI,SDLK_LGUI});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_RCTRL,SDLK_RCTRL});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_RSHIFT,SDLK_RSHIFT});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_RALT,SDLK_RALT});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_RGUI,SDLK_RGUI});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_MODE,SDLK_MODE});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_AUDIONEXT,SDLK_AUDIONEXT});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_AUDIOPREV,SDLK_AUDIOPREV});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_AUDIOSTOP,SDLK_AUDIOSTOP});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_AUDIOPLAY,SDLK_AUDIOPLAY});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_AUDIOMUTE,SDLK_AUDIOMUTE});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_MEDIASELECT,SDLK_MEDIASELECT});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_WWW,SDLK_WWW});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_MAIL,SDLK_MAIL});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_CALCULATOR,SDLK_CALCULATOR});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_COMPUTER,SDLK_COMPUTER});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_AC_SEARCH,SDLK_AC_SEARCH});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_AC_HOME,SDLK_AC_HOME});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_AC_BACK,SDLK_AC_BACK});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_AC_FORWARD,SDLK_AC_FORWARD});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_AC_STOP,SDLK_AC_STOP});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_AC_REFRESH,SDLK_AC_REFRESH});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_AC_BOOKMARKS,SDLK_AC_BOOKMARKS});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_BRIGHTNESSDOWN,SDLK_BRIGHTNESSDOWN});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_BRIGHTNESSUP,SDLK_BRIGHTNESSUP});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_DISPLAYSWITCH,SDLK_DISPLAYSWITCH});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KBDILLUMTOGGLE,SDLK_KBDILLUMTOGGLE});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KBDILLUMDOWN,SDLK_KBDILLUMDOWN});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_KBDILLUMUP,SDLK_KBDILLUMUP});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_EJECT,SDLK_EJECT});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_SLEEP,SDLK_SLEEP});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_APP1,SDLK_APP1});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_APP2,SDLK_APP2});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_AUDIOREWIND,SDLK_AUDIOREWIND});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_AUDIOFASTFORWARD,SDLK_AUDIOFASTFORWARD});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_SOFTLEFT,SDLK_SOFTLEFT});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_SOFTRIGHT,SDLK_SOFTRIGHT});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_CALL,SDLK_CALL});
    keyValueToKeycode.insert({ Spite::KeyValue::KV_ENDCALL,SDLK_ENDCALL});

    //KeyLocations
    keyLocationToScancode.insert({ Spite::KeyLocation::KL_UNKNOWN, SDL_SCANCODE_UNKNOWN });
    keyLocationToScancode.insert({Spite::KeyLocation::KL_A, SDL_SCANCODE_A});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_B, SDL_SCANCODE_B});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_C, SDL_SCANCODE_C});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_D, SDL_SCANCODE_D});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_E, SDL_SCANCODE_E});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_F, SDL_SCANCODE_F});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_G, SDL_SCANCODE_G});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_H, SDL_SCANCODE_H});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_I, SDL_SCANCODE_I});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_J, SDL_SCANCODE_J});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_K, SDL_SCANCODE_K});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_L, SDL_SCANCODE_L});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_M, SDL_SCANCODE_M});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_N, SDL_SCANCODE_N});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_O, SDL_SCANCODE_O});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_P, SDL_SCANCODE_P});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_Q, SDL_SCANCODE_Q});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_R, SDL_SCANCODE_R});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_S, SDL_SCANCODE_S});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_T, SDL_SCANCODE_T});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_U, SDL_SCANCODE_U});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_V, SDL_SCANCODE_V});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_W, SDL_SCANCODE_W});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_X, SDL_SCANCODE_X});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_Y, SDL_SCANCODE_Y});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_Z, SDL_SCANCODE_Z});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_1, SDL_SCANCODE_1});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_2, SDL_SCANCODE_2});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_3, SDL_SCANCODE_3});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_4, SDL_SCANCODE_4});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_5, SDL_SCANCODE_5});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_6, SDL_SCANCODE_6});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_7, SDL_SCANCODE_7});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_8, SDL_SCANCODE_8});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_9, SDL_SCANCODE_9});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_0, SDL_SCANCODE_0});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_RETURN, SDL_SCANCODE_RETURN});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_ESCAPE, SDL_SCANCODE_ESCAPE});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_BACKSPACE, SDL_SCANCODE_BACKSPACE});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_TAB, SDL_SCANCODE_TAB});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_SPACE, SDL_SCANCODE_SPACE});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_MINUS, SDL_SCANCODE_MINUS});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_EQUALS, SDL_SCANCODE_EQUALS});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_LEFTBRACKET, SDL_SCANCODE_LEFTBRACKET});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_RIGHTBRACKET, SDL_SCANCODE_RIGHTBRACKET});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_BACKSLASH, SDL_SCANCODE_BACKSLASH});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_NONUSHASH, SDL_SCANCODE_NONUSHASH});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_SEMICOLON, SDL_SCANCODE_SEMICOLON});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_APOSTROPHE, SDL_SCANCODE_APOSTROPHE});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_GRAVE, SDL_SCANCODE_GRAVE});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_COMMA, SDL_SCANCODE_COMMA});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_PERIOD, SDL_SCANCODE_PERIOD});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_SLASH, SDL_SCANCODE_SLASH});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_CAPSLOCK, SDL_SCANCODE_CAPSLOCK});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_F1, SDL_SCANCODE_F1});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_F2, SDL_SCANCODE_F2});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_F3, SDL_SCANCODE_F3});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_F4, SDL_SCANCODE_F4});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_F5, SDL_SCANCODE_F5});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_F6, SDL_SCANCODE_F6});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_F7, SDL_SCANCODE_F7});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_F8, SDL_SCANCODE_F8});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_F9, SDL_SCANCODE_F9});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_F10, SDL_SCANCODE_F10});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_F11, SDL_SCANCODE_F11});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_F12, SDL_SCANCODE_F12});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_PRINTSCREEN, SDL_SCANCODE_PRINTSCREEN});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_SCROLLLOCK, SDL_SCANCODE_SCROLLLOCK});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_PAUSE, SDL_SCANCODE_PAUSE});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_INSERT, SDL_SCANCODE_INSERT});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_HOME, SDL_SCANCODE_HOME});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_PAGEUP, SDL_SCANCODE_PAGEUP});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_DELETE, SDL_SCANCODE_DELETE});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_END, SDL_SCANCODE_END});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_PAGEDOWN, SDL_SCANCODE_PAGEDOWN});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_RIGHT, SDL_SCANCODE_RIGHT});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_LEFT, SDL_SCANCODE_LEFT});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_DOWN, SDL_SCANCODE_DOWN});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_UP, SDL_SCANCODE_UP});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_NUMLOCKCLEAR, SDL_SCANCODE_NUMLOCKCLEAR});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_DIVIDE, SDL_SCANCODE_KP_DIVIDE});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_MULTIPLY, SDL_SCANCODE_KP_MULTIPLY});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_MINUS, SDL_SCANCODE_KP_MINUS});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_PLUS, SDL_SCANCODE_KP_PLUS});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_ENTER, SDL_SCANCODE_KP_ENTER});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_1, SDL_SCANCODE_KP_1});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_2, SDL_SCANCODE_KP_2});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_3, SDL_SCANCODE_KP_3});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_4, SDL_SCANCODE_KP_4});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_5, SDL_SCANCODE_KP_5});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_6, SDL_SCANCODE_KP_6});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_7, SDL_SCANCODE_KP_7});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_8, SDL_SCANCODE_KP_8});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_9, SDL_SCANCODE_KP_9});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_0, SDL_SCANCODE_KP_0});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_PERIOD, SDL_SCANCODE_KP_PERIOD});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_NONUSBACKSLASH, SDL_SCANCODE_NONUSBACKSLASH});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_APPLICATION, SDL_SCANCODE_APPLICATION});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_POWER, SDL_SCANCODE_POWER});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_EQUALS, SDL_SCANCODE_KP_EQUALS});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_F13, SDL_SCANCODE_F13});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_F14, SDL_SCANCODE_F14});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_F15, SDL_SCANCODE_F15});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_F16, SDL_SCANCODE_F16});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_F17, SDL_SCANCODE_F17});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_F18, SDL_SCANCODE_F18});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_F19, SDL_SCANCODE_F19});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_F20, SDL_SCANCODE_F20});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_F21, SDL_SCANCODE_F21});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_F22, SDL_SCANCODE_F22});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_F23, SDL_SCANCODE_F23});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_F24, SDL_SCANCODE_F24});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_EXECUTE, SDL_SCANCODE_EXECUTE});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_HELP, SDL_SCANCODE_HELP});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_MENU, SDL_SCANCODE_MENU});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_SELECT, SDL_SCANCODE_SELECT});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_STOP, SDL_SCANCODE_STOP});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_AGAIN, SDL_SCANCODE_AGAIN});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_UNDO, SDL_SCANCODE_UNDO});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_CUT, SDL_SCANCODE_CUT});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_COPY, SDL_SCANCODE_COPY});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_PASTE, SDL_SCANCODE_PASTE});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_FIND, SDL_SCANCODE_FIND});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_MUTE, SDL_SCANCODE_MUTE});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_VOLUMEUP, SDL_SCANCODE_VOLUMEUP});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_VOLUMEDOWN, SDL_SCANCODE_VOLUMEDOWN});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_COMMA, SDL_SCANCODE_KP_COMMA});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_EQUALSAS400, SDL_SCANCODE_KP_EQUALSAS400});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_INTERNATIONAL1, SDL_SCANCODE_INTERNATIONAL1});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_INTERNATIONAL2, SDL_SCANCODE_INTERNATIONAL2});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_INTERNATIONAL3, SDL_SCANCODE_INTERNATIONAL3});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_INTERNATIONAL4, SDL_SCANCODE_INTERNATIONAL4});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_INTERNATIONAL5, SDL_SCANCODE_INTERNATIONAL5});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_INTERNATIONAL6, SDL_SCANCODE_INTERNATIONAL6});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_INTERNATIONAL7, SDL_SCANCODE_INTERNATIONAL7});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_INTERNATIONAL8, SDL_SCANCODE_INTERNATIONAL8});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_INTERNATIONAL9, SDL_SCANCODE_INTERNATIONAL9});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_LANG1, SDL_SCANCODE_LANG1});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_LANG2, SDL_SCANCODE_LANG2});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_LANG3, SDL_SCANCODE_LANG3});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_LANG4, SDL_SCANCODE_LANG4});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_LANG5, SDL_SCANCODE_LANG5});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_LANG6, SDL_SCANCODE_LANG6});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_LANG7, SDL_SCANCODE_LANG7});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_LANG8, SDL_SCANCODE_LANG8});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_LANG9, SDL_SCANCODE_LANG9});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_ALTERASE, SDL_SCANCODE_ALTERASE});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_SYSREQ, SDL_SCANCODE_SYSREQ});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_CANCEL, SDL_SCANCODE_CANCEL});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_CLEAR, SDL_SCANCODE_CLEAR});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_PRIOR, SDL_SCANCODE_PRIOR});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_RETURN2, SDL_SCANCODE_RETURN2});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_SEPARATOR, SDL_SCANCODE_SEPARATOR});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_OUT, SDL_SCANCODE_OUT});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_OPER, SDL_SCANCODE_OPER});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_CLEARAGAIN, SDL_SCANCODE_CLEARAGAIN});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_CRSEL, SDL_SCANCODE_CRSEL});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_EXSEL, SDL_SCANCODE_EXSEL});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_00, SDL_SCANCODE_KP_00});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_000, SDL_SCANCODE_KP_000});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_THOUSANDSSEPARATOR, SDL_SCANCODE_THOUSANDSSEPARATOR});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_DECIMALSEPARATOR, SDL_SCANCODE_DECIMALSEPARATOR});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_CURRENCYUNIT, SDL_SCANCODE_CURRENCYUNIT});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_CURRENCYSUBUNIT, SDL_SCANCODE_CURRENCYSUBUNIT});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_LEFTPAREN, SDL_SCANCODE_KP_LEFTPAREN});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_RIGHTPAREN, SDL_SCANCODE_KP_RIGHTPAREN});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_LEFTBRACE, SDL_SCANCODE_KP_LEFTBRACE});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_RIGHTBRACE, SDL_SCANCODE_KP_RIGHTBRACE});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_TAB, SDL_SCANCODE_KP_TAB});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_BACKSPACE, SDL_SCANCODE_KP_BACKSPACE});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_A, SDL_SCANCODE_KP_A});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_B, SDL_SCANCODE_KP_B});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_C, SDL_SCANCODE_KP_C});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_D, SDL_SCANCODE_KP_D});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_E, SDL_SCANCODE_KP_E});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_F, SDL_SCANCODE_KP_F});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_XOR, SDL_SCANCODE_KP_XOR});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_POWER, SDL_SCANCODE_KP_POWER});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_PERCENT, SDL_SCANCODE_KP_PERCENT});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_LESS, SDL_SCANCODE_KP_LESS});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_GREATER, SDL_SCANCODE_KP_GREATER});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_AMPERSAND, SDL_SCANCODE_KP_AMPERSAND});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_DBLAMPERSAND, SDL_SCANCODE_KP_DBLAMPERSAND});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_VERTICALBAR, SDL_SCANCODE_KP_VERTICALBAR});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_DBLVERTICALBAR, SDL_SCANCODE_KP_DBLVERTICALBAR});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_COLON, SDL_SCANCODE_KP_COLON});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_HASH, SDL_SCANCODE_KP_HASH});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_SPACE, SDL_SCANCODE_KP_SPACE});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_AT, SDL_SCANCODE_KP_AT});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_EXCLAM, SDL_SCANCODE_KP_EXCLAM});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_MEMSTORE, SDL_SCANCODE_KP_MEMSTORE});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_MEMRECALL, SDL_SCANCODE_KP_MEMRECALL});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_MEMCLEAR, SDL_SCANCODE_KP_MEMCLEAR});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_MEMADD, SDL_SCANCODE_KP_MEMADD});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_MEMSUBTRACT, SDL_SCANCODE_KP_MEMSUBTRACT});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_MEMMULTIPLY, SDL_SCANCODE_KP_MEMMULTIPLY});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_MEMDIVIDE, SDL_SCANCODE_KP_MEMDIVIDE});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_PLUSMINUS, SDL_SCANCODE_KP_PLUSMINUS});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_CLEAR, SDL_SCANCODE_KP_CLEAR});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_CLEARENTRY, SDL_SCANCODE_KP_CLEARENTRY});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_BINARY, SDL_SCANCODE_KP_BINARY});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_OCTAL, SDL_SCANCODE_KP_OCTAL});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_DECIMAL, SDL_SCANCODE_KP_DECIMAL});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KP_HEXADECIMAL, SDL_SCANCODE_KP_HEXADECIMAL});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_LCTRL, SDL_SCANCODE_LCTRL});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_LSHIFT, SDL_SCANCODE_LSHIFT});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_LALT, SDL_SCANCODE_LALT});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_LGUI, SDL_SCANCODE_LGUI});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_RCTRL, SDL_SCANCODE_RCTRL});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_RSHIFT, SDL_SCANCODE_RSHIFT});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_RALT, SDL_SCANCODE_RALT});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_RGUI, SDL_SCANCODE_RGUI});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_MODE, SDL_SCANCODE_MODE});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_AUDIONEXT, SDL_SCANCODE_AUDIONEXT});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_AUDIOPREV, SDL_SCANCODE_AUDIOPREV});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_AUDIOSTOP, SDL_SCANCODE_AUDIOSTOP});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_AUDIOPLAY, SDL_SCANCODE_AUDIOPLAY});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_AUDIOMUTE, SDL_SCANCODE_AUDIOMUTE});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_MEDIASELECT, SDL_SCANCODE_MEDIASELECT});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_WWW, SDL_SCANCODE_WWW});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_MAIL, SDL_SCANCODE_MAIL});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_CALCULATOR, SDL_SCANCODE_CALCULATOR});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_COMPUTER, SDL_SCANCODE_COMPUTER});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_AC_SEARCH, SDL_SCANCODE_AC_SEARCH});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_AC_HOME, SDL_SCANCODE_AC_HOME});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_AC_BACK, SDL_SCANCODE_AC_BACK});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_AC_FORWARD, SDL_SCANCODE_AC_FORWARD});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_AC_STOP, SDL_SCANCODE_AC_STOP});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_AC_REFRESH, SDL_SCANCODE_AC_REFRESH});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_AC_BOOKMARKS, SDL_SCANCODE_AC_BOOKMARKS});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_BRIGHTNESSDOWN, SDL_SCANCODE_BRIGHTNESSDOWN});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_BRIGHTNESSUP, SDL_SCANCODE_BRIGHTNESSUP});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_DISPLAYSWITCH, SDL_SCANCODE_DISPLAYSWITCH});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KBDILLUMTOGGLE, SDL_SCANCODE_KBDILLUMTOGGLE});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KBDILLUMDOWN, SDL_SCANCODE_KBDILLUMDOWN});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_KBDILLUMUP, SDL_SCANCODE_KBDILLUMUP});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_EJECT, SDL_SCANCODE_EJECT});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_SLEEP, SDL_SCANCODE_SLEEP});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_APP1, SDL_SCANCODE_APP1});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_APP2, SDL_SCANCODE_APP2});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_AUDIOREWIND, SDL_SCANCODE_AUDIOREWIND});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_AUDIOFASTFORWARD, SDL_SCANCODE_AUDIOFASTFORWARD});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_SOFTLEFT, SDL_SCANCODE_SOFTLEFT});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_SOFTRIGHT, SDL_SCANCODE_SOFTRIGHT});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_CALL, SDL_SCANCODE_CALL});
    keyLocationToScancode.insert({Spite::KeyLocation::KL_ENDCALL, SDL_SCANCODE_ENDCALL});

    for(const auto& pair : keyValueToKeycode) {
        keycodeToKeyValue.insert({pair.second, pair.first});
    }

    for (const auto& pair : keyLocationToScancode) {
        scancodeToKeyLocation.insert({ pair.second, pair.first });
    }

    return 0;
}

int Spite::EventSystem_SDL::Shutdown()
{
    return 0;
}

int Spite::EventSystem_SDL::ProcessEvents()
{
    SDL_Event e;
    //While application is running
    int returnValue = 0;

    //Standard SDL event system - go look at their documentation if you care!
    //Handle events on queue
    while (SDL_PollEvent(&e) != 0)
    {
        switch (e.type)
        {
        case SDL_QUIT:
            //User requests quit
            returnValue = -1;
            break;
        case SDL_KEYDOWN:
            keyDownRenderCount[(size_t)e.key.keysym.scancode]++;
            keyDownUpdateCount[(size_t)e.key.keysym.scancode]++;
            break;
        case SDL_KEYUP:
            keyUpRenderCount[(size_t)e.key.keysym.scancode]++;
            keyUpUpdateCount[(size_t)e.key.keysym.scancode]++;
            break;
        case SDL_WINDOWEVENT:
            //Here we're converting the SDL event into our generic Spite event
            //so that we can keep things nice and abstract
            GR_WindowEvent we;
            {                
                we.event = static_cast<RenderSystem::GR_WINDOWEVENT>(e.window.event);
                we.data1 = e.window.data1;
                we.data2 = e.window.data2;
                we.padding1 = e.window.padding1;
                we.padding2 = e.window.padding2;
                we.padding3 = e.window.padding3;
                we.timestamp = e.window.timestamp;
                we.type = e.window.type;
                we.windowID = e.window.windowID;
            }
            Spite::render->HandleWindowEvent(we);
            break;
        }
    }
    return returnValue;
}

bool Spite::EventSystem_SDL::IsPressed(KeyValue key) {
    SDL_Scancode code = SDL_GetScancodeFromKey(ConvertToSDLKeycode(key));
    if(code == SDL_SCANCODE_UNKNOWN) {
        std::cout << std::format("Cannot get scancode of key {}", (int)key) << std::endl;
        return false;
    }
    if(code >= keyboardState.size()) {
        std::cout << std::format("Cannot get key state for scancode {} with keyboard state array of size {}", (int)code, keyboardState.size()) << std::endl;
        return false;
    }
    return keyboardState[code] > 0;
}

bool Spite::EventSystem_SDL::IsPressed(KeyLocation key) {
    SDL_Scancode code = ConvertToSDLScancode(key);
    if (code >= keyboardState.size()) {
        std::cout << std::format("Cannot get key state for scancode {} with keyboard state array of size {}", (int)code, keyboardState.size()) << std::endl;
        return false;
    }
    return keyboardState[code] > 0;
}

int Spite::EventSystem_SDL::GetDownCount(KeyValue key) {
    SDL_Scancode code = SDL_GetScancodeFromKey(ConvertToSDLKeycode(key));
    if (code == SDL_SCANCODE_UNKNOWN) {
        std::cout << std::format("Cannot get scancode of key {}", (int)key) << std::endl;
        return 0;
    }
    if(inputMode == InputMode::UPDATE) {
        return keyDownUpdateCount[code];
    }else {
        return keyDownRenderCount[code];
    }
}

int Spite::EventSystem_SDL::GetDownCount(KeyLocation key) {
    SDL_Scancode code = ConvertToSDLScancode(key);
    if (code == SDL_SCANCODE_UNKNOWN) {
        std::cout << std::format("Cannot get scancode of key {}", (int)key) << std::endl;
        return 0;
    }
    if (inputMode == InputMode::UPDATE) {
        return keyDownUpdateCount[code];
    } else {
        return keyDownRenderCount[code];
    }
}

int Spite::EventSystem_SDL::GetUpCount(KeyValue key) {
    SDL_Scancode code = SDL_GetScancodeFromKey(ConvertToSDLKeycode(key));
    if (code == SDL_SCANCODE_UNKNOWN) {
        std::cout << std::format("Cannot get scancode of key {}", (int)key) << std::endl;
        return 0;
    }
    if (inputMode == InputMode::UPDATE) {
        return keyUpUpdateCount[code];
    } else {
        return keyUpRenderCount[code];
    }
}

int Spite::EventSystem_SDL::GetUpCount(KeyLocation key) {
    SDL_Scancode code = ConvertToSDLScancode(key);
    if (code == SDL_SCANCODE_UNKNOWN) {
        std::cout << std::format("Cannot get scancode of key {}", (int)key) << std::endl;
        return 0;
    }
    if (inputMode == InputMode::UPDATE) {
        return keyUpUpdateCount[code];
    } else {
        return keyUpRenderCount[code];
    }
}

void Spite::EventSystem_SDL::UpdateStart() {
    inputMode = InputMode::UPDATE;
}

void Spite::EventSystem_SDL::UpdateEnd() {
    std::ranges::fill(keyDownUpdateCount, 0);
    std::ranges::fill(keyUpUpdateCount, 0);
}

void Spite::EventSystem_SDL::RenderStart() {
    inputMode = InputMode::RENDER;
}

void Spite::EventSystem_SDL::RenderEnd() {
    std::ranges::fill(keyDownRenderCount, 0);
    std::ranges::fill(keyUpRenderCount, 0);
}

SDL_Scancode Spite::EventSystem_SDL::ConvertToSDLScancode(Spite::KeyLocation kl) {
    auto it = keyLocationToScancode.find(kl);
    if (it == keyLocationToScancode.end()) {
        std::cout << "Could not find SDL Scancode for KeyLocation" << std::endl;
        return SDL_SCANCODE_UNKNOWN;
    }
    return it->second;
}

SDL_Keycode Spite::EventSystem_SDL::ConvertToSDLKeycode(Spite::KeyValue kv) {
    auto it = keyValueToKeycode.find(kv);
    if (it == keyValueToKeycode.end()) {
        std::cout << "Could not find SDL Keycode for KeyValue" << std::endl;
        return SDLK_UNKNOWN;
    }
    return it->second;
}
