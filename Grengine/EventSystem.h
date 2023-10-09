#pragma once
#include "Subsystem.h"
#include "Internal.h"

namespace Spite {
    enum class KeyValue : uint32_t {
        KV_UNKNOWN,
        KV_RETURN,
        KV_ESCAPE,
        KV_BACKSPACE,
        KV_TAB,
        KV_SPACE,
        KV_EXCLAIM,
        KV_QUOTEDBL,
        KV_HASH,
        KV_PERCENT,
        KV_DOLLAR,
        KV_AMPERSAND,
        KV_QUOTE ,
        KV_LEFTPAREN,
        KV_RIGHTPAREN,
        KV_ASTERISK,
        KV_PLUS,
        KV_COMMA,
        KV_MINUS,
        KV_PERIOD,
        KV_SLASH,
        KV_0,
        KV_1,
        KV_2,
        KV_3,
        KV_4,
        KV_5,
        KV_6,
        KV_7,
        KV_8,
        KV_9,
        KV_COLON,
        KV_SEMICOLON,
        KV_LESS,
        KV_EQUALS,
        KV_GREATER,
        KV_QUESTION,
        KV_AT,
        
        KV_LEFTBRACKET,
        KV_BACKSLASH ,
        KV_RIGHTBRACKET,
        KV_CARET,
        KV_UNDERSCORE,
        KV_BACKQUOTE,
        KV_A,
        KV_B,
        KV_C,
        KV_D,
        KV_E,
        KV_F,
        KV_G,
        KV_H,
        KV_I,
        KV_J,
        KV_K,
        KV_L,
        KV_M,
        KV_N,
        KV_O,
        KV_P,
        KV_Q,
        KV_R,
        KV_S,
        KV_T,
        KV_U,
        KV_V,
        KV_W,
        KV_X,
        KV_Y,
        KV_Z,
        KV_CAPSLOCK,
        KV_F1,
        KV_F2,
        KV_F3,
        KV_F4,
        KV_F5,
        KV_F6,
        KV_F7,
        KV_F8,
        KV_F9,
        KV_F10,
        KV_F11,
        KV_F12,
        KV_PRINTSCREEN,
        KV_SCROLLLOCK,
        KV_PAUSE,
        KV_INSERT,
        KV_HOME,
        KV_PAGEUP,
        KV_DELETE,
        KV_END,
        KV_PAGEDOWN,
        KV_RIGHT,
        KV_LEFT,
        KV_DOWN,
        KV_UP,
        KV_NUMLOCKCLEAR,
        KV_KP_DIVIDE,
        KV_KP_MULTIPLY,
        KV_KP_MINUS,
        KV_KP_PLUS,
        KV_KP_ENTER,
        KV_KP_1,
        KV_KP_2,
        KV_KP_3,
        KV_KP_4,
        KV_KP_5,
        KV_KP_6,
        KV_KP_7,
        KV_KP_8,
        KV_KP_9,
        KV_KP_0,
        KV_KP_PERIOD,
        KV_APPLICATION,
        KV_POWER,
        KV_KP_EQUALS,
        KV_F13,
        KV_F14,
        KV_F15,
        KV_F16,
        KV_F17,
        KV_F18,
        KV_F19,
        KV_F20,
        KV_F21,
        KV_F22,
        KV_F23,
        KV_F24,
        KV_EXECUTE,
        KV_HELP,
        KV_MENU,
        KV_SELECT,
        KV_STOP,
        KV_AGAIN,
        KV_UNDO,
        KV_CUT,
        KV_COPY,
        KV_PASTE,
        KV_FIND,
        KV_MUTE,
        KV_VOLUMEUP,
        KV_VOLUMEDOWN,
        KV_KP_COMMA,
        KV_KP_EQUALSAS400,
        
        KV_ALTERASE,
        KV_SYSREQ,
        KV_CANCEL,
        KV_CLEAR,
        KV_PRIOR,
        KV_RETURN2,
        KV_SEPARATOR,
        KV_OUT,
        KV_OPER,
        KV_CLEARAGAIN,
        KV_CRSEL,
        KV_EXSEL,
        
        KV_KP_00,
        KV_KP_000,
        KV_THOUSANDSSEPARATOR,
        KV_DECIMALSEPARATOR,
        KV_CURRENCYUNIT,
        KV_CURRENCYSUBUNIT,
        KV_KP_LEFTPAREN,
        KV_KP_RIGHTPAREN,
        KV_KP_LEFTBRACE,
        KV_KP_RIGHTBRACE,
        KV_KP_TAB,
        KV_KP_BACKSPACE,
        KV_KP_A,
        KV_KP_B,
        KV_KP_C,
        KV_KP_D,
        KV_KP_E,
        KV_KP_F,
        KV_KP_XOR,
        KV_KP_POWER,
        KV_KP_PERCENT,
        KV_KP_LESS,
        KV_KP_GREATER,
        KV_KP_AMPERSAND,
        KV_KP_DBLAMPERSAND,
        KV_KP_VERTICALBAR,
        KV_KP_DBLVERTICALBAR,
        KV_KP_COLON,
        KV_KP_HASH,
        KV_KP_SPACE,
        KV_KP_AT,
        KV_KP_EXCLAM,
        KV_KP_MEMSTORE,
        KV_KP_MEMRECALL,
        KV_KP_MEMCLEAR,
        KV_KP_MEMADD,
        KV_KP_MEMSUBTRACT,
        KV_KP_MEMMULTIPLY,
        KV_KP_MEMDIVIDE,
        KV_KP_PLUSMINUS,
        KV_KP_CLEAR,
        KV_KP_CLEARENTRY,
        KV_KP_BINARY,
        KV_KP_OCTAL,
        KV_KP_DECIMAL,
        KV_KP_HEXADECIMAL,
        
        KV_LCTRL,
        KV_LSHIFT,
        KV_LALT,
        KV_LGUI,
        KV_RCTRL,
        KV_RSHIFT,
        KV_RALT,
        KV_RGUI,

        KV_MODE,

        KV_AUDIONEXT,
        KV_AUDIOPREV,
        KV_AUDIOSTOP,
        KV_AUDIOPLAY,
        KV_AUDIOMUTE,
        KV_MEDIASELECT,
        KV_WWW,
        KV_MAIL,
        KV_CALCULATOR,
        KV_COMPUTER,
        KV_AC_SEARCH,
        KV_AC_HOME,
        KV_AC_BACK,
        KV_AC_FORWARD,
        KV_AC_STOP,
        KV_AC_REFRESH,
        KV_AC_BOOKMARKS,

        KV_BRIGHTNESSDOWN,
        KV_BRIGHTNESSUP,
        KV_DISPLAYSWITCH,
        KV_KBDILLUMTOGGLE,
        KV_KBDILLUMDOWN,
        KV_KBDILLUMUP,
        KV_EJECT,
        KV_SLEEP,
        KV_APP1,
        KV_APP2,

        KV_AUDIOREWIND,
        KV_AUDIOFASTFORWARD,

        KV_SOFTLEFT,
        KV_SOFTRIGHT,
        KV_CALL,
        KV_ENDCALL
    };

    enum class KeyLocation : uint32_t {
        KL_UNKNOWN = 0,

        /**
         *  \name Usage page 0x07
         *
         *  These values are from usage page 0x07 (USB keyboard page).
         */
         /* @{ */

        KL_A = 4,
        KL_B = 5,
        KL_C = 6,
        KL_D = 7,
        KL_E = 8,
        KL_F = 9,
        KL_G = 10,
        KL_H = 11,
        KL_I = 12,
        KL_J = 13,
        KL_K = 14,
        KL_L = 15,
        KL_M = 16,
        KL_N = 17,
        KL_O = 18,
        KL_P = 19,
        KL_Q = 20,
        KL_R = 21,
        KL_S = 22,
        KL_T = 23,
        KL_U = 24,
        KL_V = 25,
        KL_W = 26,
        KL_X = 27,
        KL_Y = 28,
        KL_Z = 29,

        KL_1 = 30,
        KL_2 = 31,
        KL_3 = 32,
        KL_4 = 33,
        KL_5 = 34,
        KL_6 = 35,
        KL_7 = 36,
        KL_8 = 37,
        KL_9 = 38,
        KL_0 = 39,

        KL_RETURN = 40,
        KL_ESCAPE = 41,
        KL_BACKSPACE = 42,
        KL_TAB = 43,
        KL_SPACE = 44,

        KL_MINUS = 45,
        KL_EQUALS = 46,
        KL_LEFTBRACKET = 47,
        KL_RIGHTBRACKET = 48,
        KL_BACKSLASH = 49, /**< Located at the lower left of the return
                                      *   key on ISO keyboards and at the right end
                                      *   of the QWERTY row on ANSI keyboards.
                                      *   Produces REVERSE SOLIDUS (backslash) and
                                      *   VERTICAL LINE in a US layout, REVERSE
                                      *   SOLIDUS and VERTICAL LINE in a UK Mac
                                      *   layout, NUMBER SIGN and TILDE in a UK
                                      *   Windows layout, DOLLAR SIGN and POUND SIGN
                                      *   in a Swiss German layout, NUMBER SIGN and
                                      *   APOSTROPHE in a German layout, GRAVE
                                      *   ACCENT and POUND SIGN in a French Mac
                                      *   layout, and ASTERISK and MICRO SIGN in a
                                      *   French Windows layout.
                                      */
        KL_NONUSHASH = 50, /**< ISO USB keyboards actually use this code
                                      *   instead of 49 for the same key, but all
                                      *   OSes I've seen treat the two codes
                                      *   identically. So, as an implementor, unless
                                      *   your keyboard generates both of those
                                      *   codes and your OS treats them differently,
                                      *   you should generate KL_BACKSLASH
                                      *   instead of this code. As a user, you
                                      *   should not rely on this code because SDL
                                      *   will never generate it with most (all?)
                                      *   keyboards.
                                      */
        KL_SEMICOLON = 51,
        KL_APOSTROPHE = 52,
        KL_GRAVE = 53, /**< Located in the top left corner (on both ANSI
                                  *   and ISO keyboards). Produces GRAVE ACCENT and
                                  *   TILDE in a US Windows layout and in US and UK
                                  *   Mac layouts on ANSI keyboards, GRAVE ACCENT
                                  *   and NOT SIGN in a UK Windows layout, SECTION
                                  *   SIGN and PLUS-MINUS SIGN in US and UK Mac
                                  *   layouts on ISO keyboards, SECTION SIGN and
                                  *   DEGREE SIGN in a Swiss German layout (Mac:
                                  *   only on ISO keyboards), CIRCUMFLEX ACCENT and
                                  *   DEGREE SIGN in a German layout (Mac: only on
                                  *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
                                  *   French Windows layout, COMMERCIAL AT and
                                  *   NUMBER SIGN in a French Mac layout on ISO
                                  *   keyboards, and LESS-THAN SIGN and GREATER-THAN
                                  *   SIGN in a Swiss German, German, or French Mac
                                  *   layout on ANSI keyboards.
                                  */
        KL_COMMA = 54,
        KL_PERIOD = 55,
        KL_SLASH = 56,

        KL_CAPSLOCK = 57,

        KL_F1 = 58,
        KL_F2 = 59,
        KL_F3 = 60,
        KL_F4 = 61,
        KL_F5 = 62,
        KL_F6 = 63,
        KL_F7 = 64,
        KL_F8 = 65,
        KL_F9 = 66,
        KL_F10 = 67,
        KL_F11 = 68,
        KL_F12 = 69,

        KL_PRINTSCREEN = 70,
        KL_SCROLLLOCK = 71,
        KL_PAUSE = 72,
        KL_INSERT = 73, /**< insert on PC, help on some Mac keyboards (but
                                       does send code 73, not 117) */
        KL_HOME = 74,
        KL_PAGEUP = 75,
        KL_DELETE = 76,
        KL_END = 77,
        KL_PAGEDOWN = 78,
        KL_RIGHT = 79,
        KL_LEFT = 80,
        KL_DOWN = 81,
        KL_UP = 82,

        KL_NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards
                                         */
        KL_KP_DIVIDE = 84,
        KL_KP_MULTIPLY = 85,
        KL_KP_MINUS = 86,
        KL_KP_PLUS = 87,
        KL_KP_ENTER = 88,
        KL_KP_1 = 89,
        KL_KP_2 = 90,
        KL_KP_3 = 91,
        KL_KP_4 = 92,
        KL_KP_5 = 93,
        KL_KP_6 = 94,
        KL_KP_7 = 95,
        KL_KP_8 = 96,
        KL_KP_9 = 97,
        KL_KP_0 = 98,
        KL_KP_PERIOD = 99,

        KL_NONUSBACKSLASH = 100, /**< This is the additional key that ISO
                                            *   keyboards have over ANSI ones,
                                            *   located between left shift and Y.
                                            *   Produces GRAVE ACCENT and TILDE in a
                                            *   US or UK Mac layout, REVERSE SOLIDUS
                                            *   (backslash) and VERTICAL LINE in a
                                            *   US or UK Windows layout, and
                                            *   LESS-THAN SIGN and GREATER-THAN SIGN
                                            *   in a Swiss German, German, or French
                                            *   layout. */
        KL_APPLICATION = 101, /**< windows contextual menu, compose */
        KL_POWER = 102, /**< The USB document says this is a status flag,
                                   *   not a physical key - but some Mac keyboards
                                   *   do have a power key. */
        KL_KP_EQUALS = 103,
        KL_F13 = 104,
        KL_F14 = 105,
        KL_F15 = 106,
        KL_F16 = 107,
        KL_F17 = 108,
        KL_F18 = 109,
        KL_F19 = 110,
        KL_F20 = 111,
        KL_F21 = 112,
        KL_F22 = 113,
        KL_F23 = 114,
        KL_F24 = 115,
        KL_EXECUTE = 116,
        KL_HELP = 117,    /**< AL Integrated Help Center */
        KL_MENU = 118,    /**< Menu (show menu) */
        KL_SELECT = 119,
        KL_STOP = 120,    /**< AC Stop */
        KL_AGAIN = 121,   /**< AC Redo/Repeat */
        KL_UNDO = 122,    /**< AC Undo */
        KL_CUT = 123,     /**< AC Cut */
        KL_COPY = 124,    /**< AC Copy */
        KL_PASTE = 125,   /**< AC Paste */
        KL_FIND = 126,    /**< AC Find */
        KL_MUTE = 127,
        KL_VOLUMEUP = 128,
        KL_VOLUMEDOWN = 129,
        /* not sure whether there's a reason to enable these */
        /*     KL_LOCKINGCAPSLOCK = 130,  */
        /*     KL_LOCKINGNUMLOCK = 131, */
        /*     KL_LOCKINGSCROLLLOCK = 132, */
        KL_KP_COMMA = 133,
        KL_KP_EQUALSAS400 = 134,

        KL_INTERNATIONAL1 = 135, /**< used on Asian keyboards, see
                                                footnotes in USB doc */
        KL_INTERNATIONAL2 = 136,
        KL_INTERNATIONAL3 = 137, /**< Yen */
        KL_INTERNATIONAL4 = 138,
        KL_INTERNATIONAL5 = 139,
        KL_INTERNATIONAL6 = 140,
        KL_INTERNATIONAL7 = 141,
        KL_INTERNATIONAL8 = 142,
        KL_INTERNATIONAL9 = 143,
        KL_LANG1 = 144, /**< Hangul/English toggle */
        KL_LANG2 = 145, /**< Hanja conversion */
        KL_LANG3 = 146, /**< Katakana */
        KL_LANG4 = 147, /**< Hiragana */
        KL_LANG5 = 148, /**< Zenkaku/Hankaku */
        KL_LANG6 = 149, /**< reserved */
        KL_LANG7 = 150, /**< reserved */
        KL_LANG8 = 151, /**< reserved */
        KL_LANG9 = 152, /**< reserved */

        KL_ALTERASE = 153,    /**< Erase-Eaze */
        KL_SYSREQ = 154,
        KL_CANCEL = 155,      /**< AC Cancel */
        KL_CLEAR = 156,
        KL_PRIOR = 157,
        KL_RETURN2 = 158,
        KL_SEPARATOR = 159,
        KL_OUT = 160,
        KL_OPER = 161,
        KL_CLEARAGAIN = 162,
        KL_CRSEL = 163,
        KL_EXSEL = 164,

        KL_KP_00 = 176,
        KL_KP_000 = 177,
        KL_THOUSANDSSEPARATOR = 178,
        KL_DECIMALSEPARATOR = 179,
        KL_CURRENCYUNIT = 180,
        KL_CURRENCYSUBUNIT = 181,
        KL_KP_LEFTPAREN = 182,
        KL_KP_RIGHTPAREN = 183,
        KL_KP_LEFTBRACE = 184,
        KL_KP_RIGHTBRACE = 185,
        KL_KP_TAB = 186,
        KL_KP_BACKSPACE = 187,
        KL_KP_A = 188,
        KL_KP_B = 189,
        KL_KP_C = 190,
        KL_KP_D = 191,
        KL_KP_E = 192,
        KL_KP_F = 193,
        KL_KP_XOR = 194,
        KL_KP_POWER = 195,
        KL_KP_PERCENT = 196,
        KL_KP_LESS = 197,
        KL_KP_GREATER = 198,
        KL_KP_AMPERSAND = 199,
        KL_KP_DBLAMPERSAND = 200,
        KL_KP_VERTICALBAR = 201,
        KL_KP_DBLVERTICALBAR = 202,
        KL_KP_COLON = 203,
        KL_KP_HASH = 204,
        KL_KP_SPACE = 205,
        KL_KP_AT = 206,
        KL_KP_EXCLAM = 207,
        KL_KP_MEMSTORE = 208,
        KL_KP_MEMRECALL = 209,
        KL_KP_MEMCLEAR = 210,
        KL_KP_MEMADD = 211,
        KL_KP_MEMSUBTRACT = 212,
        KL_KP_MEMMULTIPLY = 213,
        KL_KP_MEMDIVIDE = 214,
        KL_KP_PLUSMINUS = 215,
        KL_KP_CLEAR = 216,
        KL_KP_CLEARENTRY = 217,
        KL_KP_BINARY = 218,
        KL_KP_OCTAL = 219,
        KL_KP_DECIMAL = 220,
        KL_KP_HEXADECIMAL = 221,

        KL_LCTRL = 224,
        KL_LSHIFT = 225,
        KL_LALT = 226, /**< alt, option */
        KL_LGUI = 227, /**< windows, command (apple), meta */
        KL_RCTRL = 228,
        KL_RSHIFT = 229,
        KL_RALT = 230, /**< alt gr, option */
        KL_RGUI = 231, /**< windows, command (apple), meta */

        KL_MODE = 257,    /**< I'm not sure if this is really not covered
                                     *   by any of the above, but since there's a
                                     *   special KMOD_MODE for it I'm adding it here
                                     */

                                     /* @} *//* Usage page 0x07 */

                                     /**
                                      *  \name Usage page 0x0C
                                      *
                                      *  These values are mapped from usage page 0x0C (USB consumer page).
                                      *  See https://usb.org/sites/default/files/hut1_2.pdf
                                      *
                                      *  There are way more keys in the spec than we can represent in the
                                      *  current scancode range, so pick the ones that commonly come up in
                                      *  real world usage.
                                      */
                                      /* @{ */

        KL_AUDIONEXT = 258,
        KL_AUDIOPREV = 259,
        KL_AUDIOSTOP = 260,
        KL_AUDIOPLAY = 261,
        KL_AUDIOMUTE = 262,
        KL_MEDIASELECT = 263,
        KL_WWW = 264,             /**< AL Internet Browser */
        KL_MAIL = 265,
        KL_CALCULATOR = 266,      /**< AL Calculator */
        KL_COMPUTER = 267,
        KL_AC_SEARCH = 268,       /**< AC Search */
        KL_AC_HOME = 269,         /**< AC Home */
        KL_AC_BACK = 270,         /**< AC Back */
        KL_AC_FORWARD = 271,      /**< AC Forward */
        KL_AC_STOP = 272,         /**< AC Stop */
        KL_AC_REFRESH = 273,      /**< AC Refresh */
        KL_AC_BOOKMARKS = 274,    /**< AC Bookmarks */

        /* @} *//* Usage page 0x0C */

        /**
         *  \name Walther keys
         *
         *  These are values that Christian Walther added (for mac keyboard?).
         */
         /* @{ */

        KL_BRIGHTNESSDOWN = 275,
        KL_BRIGHTNESSUP = 276,
        KL_DISPLAYSWITCH = 277, /**< display mirroring/dual display
                                               switch, video mode switch */
        KL_KBDILLUMTOGGLE = 278,
        KL_KBDILLUMDOWN = 279,
        KL_KBDILLUMUP = 280,
        KL_EJECT = 281,
        KL_SLEEP = 282,           /**< SC System Sleep */

        KL_APP1 = 283,
        KL_APP2 = 284,

        /* @} *//* Walther keys */

        /**
         *  \name Usage page 0x0C (additional media keys)
         *
         *  These values are mapped from usage page 0x0C (USB consumer page).
         */
         /* @{ */

        KL_AUDIOREWIND = 285,
        KL_AUDIOFASTFORWARD = 286,

        /* @} *//* Usage page 0x0C (additional media keys) */

        /**
         *  \name Mobile keys
         *
         *  These are values that are often used on mobile phones.
         */
         /* @{ */

        KL_SOFTLEFT = 287, /**< Usually situated below the display on phones and
                                          used as a multi-function feature key for selecting
                                          a software defined function shown on the bottom left
                                          of the display. */
        KL_SOFTRIGHT = 288, /**< Usually situated below the display on phones and
                                           used as a multi-function feature key for selecting
                                           a software defined function shown on the bottom right
                                           of the display. */
        KL_CALL = 289, /**< Used for accepting phone calls. */
        KL_ENDCALL = 290, /**< Used for rejecting phone calls. */

        /* @} *//* Mobile keys */

        /* Add any other keys here. */

        KL_NUM_KEYLOCATIONS = 512 /**< not a key, just marks the number of scancodes
                                     for array bounds */
    };
    
    
    /// <summary>
    /// Interface base class to our event system
    /// </summary>
    class EventSystem :
        public Subsystem
    {
        friend int Internal::ExecuteGame(int argc, char** argv);
    public:
        virtual int ProcessEvents() = 0;
        virtual bool IsPressed(KeyValue) = 0;
        virtual bool IsPressed(KeyLocation) = 0;
        virtual int GetDownCount(KeyValue) = 0;
        virtual int GetDownCount(KeyLocation) = 0;
        virtual int GetUpCount(KeyValue) = 0;
        virtual int GetUpCount(KeyLocation) = 0;
    protected:
        virtual void UpdateStart() = 0;
        virtual void UpdateEnd() = 0;
        virtual void RenderStart() = 0;
        virtual void RenderEnd() = 0;
    };

    

    extern EventSystem* event;
}
