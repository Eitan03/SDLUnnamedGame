#pragma once

#define MGL_SCANCODE_MASK (1<<30)
#define MGL_SCANCODE_TO_KEYCODE(X)  ((unsigned int )X | MGL_SCANCODE_MASK)

namespace MGL {

	enum class EventTypes {
		NONE = 0,
		QUIT,
		MOUSE_MOVED,
		MOUSE_WHEEL,
		WINDOW_EVENT,
        KEY_PRESSED,
		UNKNOWN, // this is not an error since I didnt put all of SDL events here
	};
	enum class WindowEventTypes {
		ENTER,
		LEAVE
	};

    enum class ScanCodes // copied from SDL
    {
        UNKNOWN = 0,
        /**
         *  \name Usage page 0x07
         *
         *  These values are from usage page 0x07 (USB keyboard page).
         */
         /* @{ */

        A = 4,
        B = 5,
        C = 6,
        D = 7,
        E = 8,
        F = 9,
        G = 10,
        H = 11,
        I = 12,
        J = 13,
        K = 14,
        L = 15,
        M = 16,
        N = 17,
        O = 18,
        P = 19,
        Q = 20,
        R = 21,
        S = 22,
        T = 23,
        U = 24,
        V = 25,
        W = 26,
        X = 27,
        Y = 28,
        Z = 29,

        KEY_1 = 30,
        KEY_2 = 31,
        KEY_3 = 32,
        KEY_4 = 33,
        KEY_5 = 34,
        KEY_6 = 35,
        KEY_7 = 36,
        KEY_8 = 37,
        KEY_9 = 38,
        KEY_0 = 39,

        RETURN = 40,
        ESCAPE = 41,
        BACKSPACE = 42,
        TAB = 43,
        SPACE = 44,

        MINUS = 45,
        EQUALS = 46,
        LEFTBRACKET = 47,
        RIGHTBRACKET = 48,
        BACKSLASH = 49, /**< Located at the lower left of the return
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
        NONUSHASH = 50, /**< ISO USB keyboards actually use this code
                                      *   instead of 49 for the same key, but all
                                      *   OSes I've seen treat the two codes
                                      *   identically. So, as an implementor, unless
                                      *   your keyboard generates both of those
                                      *   codes and your OS treats them differently,
                                      *   you should generate BACKSLASH
                                      *   instead of this code. As a user, you
                                      *   should not rely on this code because SDL
                                      *   will never generate it with most (all?)
                                      *   keyboards.
                                      */
        SEMICOLON = 51,
        APOSTROPHE = 52,
        GRAVE = 53, /**< Located in the top left corner (on both ANSI
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
        COMMA = 54,
        PERIOD = 55,
        SLASH = 56,

        CAPSLOCK = 57,

        F1 = 58,
        F2 = 59,
        F3 = 60,
        F4 = 61,
        F5 = 62,
        F6 = 63,
        F7 = 64,
        F8 = 65,
        F9 = 66,
        F10 = 67,
        F11 = 68,
        F12 = 69,

        PRINTSCREEN = 70,
        SCROLLLOCK = 71,
        PAUSE = 72,
        INSERT = 73, /**< insert on PC, help on some Mac keyboards (but
                                       does send code 73, not 117) */
        HOME = 74,
        PAGEUP = 75,
        DELETE = 76,
        END = 77,
        PAGEDOWN = 78,
        RIGHT = 79,
        LEFT = 80,
        DOWN = 81,
        UP = 82,

        NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards
                                         */
        KP_DIVIDE = 84,
        KP_MULTIPLY = 85,
        KP_MINUS = 86,
        KP_PLUS = 87,
        KP_ENTER = 88,
        KP_1 = 89,
        KP_2 = 90,
        KP_3 = 91,
        KP_4 = 92,
        KP_5 = 93,
        KP_6 = 94,
        KP_7 = 95,
        KP_8 = 96,
        KP_9 = 97,
        KP_0 = 98,
        KP_PERIOD = 99,

        NONUSBACKSLASH = 100, /**< This is the additional key that ISO
                                            *   keyboards have over ANSI ones,
                                            *   located between left shift and Y.
                                            *   Produces GRAVE ACCENT and TILDE in a
                                            *   US or UK Mac layout, REVERSE SOLIDUS
                                            *   (backslash) and VERTICAL LINE in a
                                            *   US or UK Windows layout, and
                                            *   LESS-THAN SIGN and GREATER-THAN SIGN
                                            *   in a Swiss German, German, or French
                                            *   layout. */
        APPLICATION = 101, /**< windows contextual menu, compose */
        POWER = 102, /**< The USB document says this is a status flag,
                                   *   not a physical key - but some Mac keyboards
                                   *   do have a power key. */
        KP_EQUALS = 103,
        F13 = 104,
        F14 = 105,
        F15 = 106,
        F16 = 107,
        F17 = 108,
        F18 = 109,
        F19 = 110,
        F20 = 111,
        F21 = 112,
        F22 = 113,
        F23 = 114,
        F24 = 115,
        EXECUTE = 116,
        HELP = 117,    /**< AL Integrated Help Center */
        MENU = 118,    /**< Menu (show menu) */
        SELECT = 119,
        STOP = 120,    /**< AC Stop */
        AGAIN = 121,   /**< AC Redo/Repeat */
        UNDO = 122,    /**< AC Undo */
        CUT = 123,     /**< AC Cut */
        COPY = 124,    /**< AC Copy */
        PASTE = 125,   /**< AC Paste */
        FIND = 126,    /**< AC Find */
        MUTE = 127,
        VOLUMEUP = 128,
        VOLUMEDOWN = 129,
        /* not sure whether there's a reason to enable these */
        /*     LOCKINGCAPSLOCK = 130,  */
        /*     LOCKINGNUMLOCK = 131, */
        /*     LOCKINGSCROLLLOCK = 132, */
        KP_COMMA = 133,
        KP_EQUALSAS400 = 134,

        INTERNATIONAL1 = 135, /**< used on Asian keyboards, see
                                                footnotes in USB doc */
        INTERNATIONAL2 = 136,
        INTERNATIONAL3 = 137, /**< Yen */
        INTERNATIONAL4 = 138,
        INTERNATIONAL5 = 139,
        INTERNATIONAL6 = 140,
        INTERNATIONAL7 = 141,
        INTERNATIONAL8 = 142,
        INTERNATIONAL9 = 143,
        LANG1 = 144, /**< Hangul/English toggle */
        LANG2 = 145, /**< Hanja conversion */
        LANG3 = 146, /**< Katakana */
        LANG4 = 147, /**< Hiragana */
        LANG5 = 148, /**< Zenkaku/Hankaku */
        LANG6 = 149, /**< reserved */
        LANG7 = 150, /**< reserved */
        LANG8 = 151, /**< reserved */
        LANG9 = 152, /**< reserved */

        ALTERASE = 153,    /**< Erase-Eaze */
        SYSREQ = 154,
        CANCEL = 155,      /**< AC Cancel */
        CLEAR = 156,
        PRIOR = 157,
        RETURN2 = 158,
        SEPARATOR = 159,
        OUT = 160,
        OPER = 161,
        CLEARAGAIN = 162,
        CRSEL = 163,
        EXSEL = 164,

        KP_00 = 176,
        KP_000 = 177,
        THOUSANDSSEPARATOR = 178,
        DECIMALSEPARATOR = 179,
        CURRENCYUNIT = 180,
        CURRENCYSUBUNIT = 181,
        KP_LEFTPAREN = 182,
        KP_RIGHTPAREN = 183,
        KP_LEFTBRACE = 184,
        KP_RIGHTBRACE = 185,
        KP_TAB = 186,
        KP_BACKSPACE = 187,
        KP_A = 188,
        KP_B = 189,
        KP_C = 190,
        KP_D = 191,
        KP_E = 192,
        KP_F = 193,
        KP_XOR = 194,
        KP_POWER = 195,
        KP_PERCENT = 196,
        KP_LESS = 197,
        KP_GREATER = 198,
        KP_AMPERSAND = 199,
        KP_DBLAMPERSAND = 200,
        KP_VERTICALBAR = 201,
        KP_DBLVERTICALBAR = 202,
        KP_COLON = 203,
        KP_HASH = 204,
        KP_SPACE = 205,
        KP_AT = 206,
        KP_EXCLAM = 207,
        KP_MEMSTORE = 208,
        KP_MEMRECALL = 209,
        KP_MEMCLEAR = 210,
        KP_MEMADD = 211,
        KP_MEMSUBTRACT = 212,
        KP_MEMMULTIPLY = 213,
        KP_MEMDIVIDE = 214,
        KP_PLUSMINUS = 215,
        KP_CLEAR = 216,
        KP_CLEARENTRY = 217,
        KP_BINARY = 218,
        KP_OCTAL = 219,
        KP_DECIMAL = 220,
        KP_HEXADECIMAL = 221,

        LCTRL = 224,
        LSHIFT = 225,
        LALT = 226, /**< alt, option */
        LGUI = 227, /**< windows, command (apple), meta */
        RCTRL = 228,
        RSHIFT = 229,
        RALT = 230, /**< alt gr, option */
        RGUI = 231, /**< windows, command (apple), meta */

        MODE = 257,    /**< I'm not sure if this is really not covered
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

        AUDIONEXT = 258,
        AUDIOPREV = 259,
        AUDIOSTOP = 260,
        AUDIOPLAY = 261,
        AUDIOMUTE = 262,
        MEDIASELECT = 263,
        WWW = 264,             /**< AL Internet Browser */
        MAIL = 265,
        CALCULATOR = 266,      /**< AL Calculator */
        COMPUTER = 267,
        AC_SEARCH = 268,       /**< AC Search */
        AC_HOME = 269,         /**< AC Home */
        AC_BACK = 270,         /**< AC Back */
        AC_FORWARD = 271,      /**< AC Forward */
        AC_STOP = 272,         /**< AC Stop */
        AC_REFRESH = 273,      /**< AC Refresh */
        AC_BOOKMARKS = 274,    /**< AC Bookmarks */

        /* @} *//* Usage page 0x0C */

        /**
         *  \name Walther keys
         *
         *  These are values that Christian Walther added (for mac keyboard?).
         */
         /* @{ */

        BRIGHTNESSDOWN = 275,
        BRIGHTNESSUP = 276,
        DISPLAYSWITCH = 277, /**< display mirroring/dual display
                                               switch, video mode switch */
        KBDILLUMTOGGLE = 278,
        KBDILLUMDOWN = 279,
        KBDILLUMUP = 280,
        EJECT = 281,
        SLEEP = 282,           /**< SC System Sleep */

        APP1 = 283,
        APP2 = 284,

        /* @} *//* Walther keys */

        /**
         *  \name Usage page 0x0C (additional media keys)
         *
         *  These values are mapped from usage page 0x0C (USB consumer page).
         */
         /* @{ */

        AUDIOREWIND = 285,
        AUDIOFASTFORWARD = 286,

        /* @} *//* Usage page 0x0C (additional media keys) */

        /**
         *  \name Mobile keys
         *
         *  These are values that are often used on mobile phones.
         */
         /* @{ */

        SOFTLEFT = 287, /**< Usually situated below the display on phones and
                                          used as a multi-function feature key for selecting
                                          a software defined function shown on the bottom left
                                          of the display. */
        SOFTRIGHT = 288, /**< Usually situated below the display on phones and
                                           used as a multi-function feature key for selecting
                                           a software defined function shown on the bottom right
                                           of the display. */
        CALL = 289, /**< Used for accepting phone calls. */
        ENDCALL = 290, /**< Used for rejecting phone calls. */

        /* @} *//* Mobile keys */

        /* Add any other keys here. */

        NUM_SCANCODES = 512 /**< not a key, just marks the number of scancodes
                                     for array bounds */
    };

	enum class KeyCodes { // copied from SDL
		UNKNOWN = 0,
		RETURN = '\r',
		ESCAPE = '\033',
		BACKSPACE = '\b',
		TAB = '\t',

		SPACE = ' ',
		EXCLAIM = '!',
		QUOTEDBL = '"',
		HASH = '#',
		PERCENT = '%',
		DOLLAR = '$',
		AMPERSAND = '&',
		QUOTE = '\'',
		LEFTPAREN = '(',
		RIGHTPAREN = ')',
		ASTERISK = '*',
		PLUS = '+',
		COMMA = ',',
		MINUS = '-',
		PERIOD = '.',
		SLASH = '/',
		KEY_0 = '0',
		KEY_1 = '1',
		KEY_2 = '2',
		KEY_3 = '3',
		KEY_4 = '4',
		KEY_5 = '5',
		KEY_6 = '6',
		KEY_7 = '7',
		KEY_8 = '8',
		KEY_9 = '9',
		COLON = ':',
		SEMICOLON = ';',
		LESS = '<',
		EQUALS = '=',
		GREATER = '>',
		QUESTION = '?',
		AT = '@',
		LEFTBRACKET = '[',
		BACKSLASH = '\\',
		RIGHTBRACKET = ']',
		CARET = '^',
		UNDERSCORE = '_',
		BACKQUOTE = '`',
		a = 'a',
		b = 'b',
		c = 'c',
		d = 'd',
		e = 'e',
		f = 'f',
		g = 'g',
		h = 'h',
		i = 'i',
		j = 'j',
		k = 'k',
		l = 'l',
		m = 'm',
		n = 'n',
		o = 'o',
		p = 'p',
		q = 'q',
		r = 'r',
		s = 's',
		t = 't',
		u = 'u',
		v = 'v',
		w = 'w',
		x = 'x',
		y = 'y',
		z = 'z',

		CAPSLOCK = MGL_SCANCODE_TO_KEYCODE(ScanCodes::CAPSLOCK),

		F1 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::F1),
		F2 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::F2),
		F3 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::F3),
		F4 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::F4),
		F5 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::F5),
		F6 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::F6),
		F7 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::F7),
		F8 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::F8),
		F9 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::F9),
		F10 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::F10),
		F11 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::F11),
		F12 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::F12),

		PRINTSCREEN = MGL_SCANCODE_TO_KEYCODE(ScanCodes::PRINTSCREEN),
		SCROLLLOCK = MGL_SCANCODE_TO_KEYCODE(ScanCodes::SCROLLLOCK),
		PAUSE = MGL_SCANCODE_TO_KEYCODE(ScanCodes::PAUSE),
		INSERT = MGL_SCANCODE_TO_KEYCODE(ScanCodes::INSERT),
		HOME = MGL_SCANCODE_TO_KEYCODE(ScanCodes::HOME),
		PAGEUP = MGL_SCANCODE_TO_KEYCODE(ScanCodes::PAGEUP),
		DELETE = '\177',
		END = MGL_SCANCODE_TO_KEYCODE(ScanCodes::END),
		PAGEDOWN = MGL_SCANCODE_TO_KEYCODE(ScanCodes::PAGEDOWN),
		RIGHT = MGL_SCANCODE_TO_KEYCODE(ScanCodes::RIGHT),
		LEFT = MGL_SCANCODE_TO_KEYCODE(ScanCodes::LEFT),
		DOWN = MGL_SCANCODE_TO_KEYCODE(ScanCodes::DOWN),
		UP = MGL_SCANCODE_TO_KEYCODE(ScanCodes::UP),

		NUMLOCKCLEAR = MGL_SCANCODE_TO_KEYCODE(ScanCodes::NUMLOCKCLEAR),
		KP_DIVIDE = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_DIVIDE),
		KP_MULTIPLY = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_MULTIPLY),
		KP_MINUS = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_MINUS),
		KP_PLUS = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_PLUS),
		KP_ENTER = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_ENTER),
		KP_1 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_1),
		KP_2 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_2),
		KP_3 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_3),
		KP_4 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_4),
		KP_5 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_5),
		KP_6 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_6),
		KP_7 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_7),
		KP_8 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_8),
		KP_9 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_9),
		KP_0 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_0),
		KP_PERIOD = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_PERIOD),

		APPLICATION = MGL_SCANCODE_TO_KEYCODE(ScanCodes::APPLICATION),
		POWER = MGL_SCANCODE_TO_KEYCODE(ScanCodes::POWER),
		KP_EQUALS = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_EQUALS),
		F13 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::F13),
		F14 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::F14),
		F15 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::F15),
		F16 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::F16),
		F17 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::F17),
		F18 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::F18),
		F19 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::F19),
		F20 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::F20),
		F21 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::F21),
		F22 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::F22),
		F23 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::F23),
		F24 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::F24),
		EXECUTE = MGL_SCANCODE_TO_KEYCODE(ScanCodes::EXECUTE),
		HELP = MGL_SCANCODE_TO_KEYCODE(ScanCodes::HELP),
		MENU = MGL_SCANCODE_TO_KEYCODE(ScanCodes::MENU),
		SELECT = MGL_SCANCODE_TO_KEYCODE(ScanCodes::SELECT),
		STOP = MGL_SCANCODE_TO_KEYCODE(ScanCodes::STOP),
		AGAIN = MGL_SCANCODE_TO_KEYCODE(ScanCodes::AGAIN),
		UNDO = MGL_SCANCODE_TO_KEYCODE(ScanCodes::UNDO),
		CUT = MGL_SCANCODE_TO_KEYCODE(ScanCodes::CUT),
		COPY = MGL_SCANCODE_TO_KEYCODE(ScanCodes::COPY),
		PASTE = MGL_SCANCODE_TO_KEYCODE(ScanCodes::PASTE),
		FIND = MGL_SCANCODE_TO_KEYCODE(ScanCodes::FIND),
		MUTE = MGL_SCANCODE_TO_KEYCODE(ScanCodes::MUTE),
		VOLUMEUP = MGL_SCANCODE_TO_KEYCODE(ScanCodes::VOLUMEUP),
		VOLUMEDOWN = MGL_SCANCODE_TO_KEYCODE(ScanCodes::VOLUMEDOWN),
		KP_COMMA = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_COMMA),
		KP_EQUALSAS400 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_EQUALSAS400),

		ALTERASE = MGL_SCANCODE_TO_KEYCODE(ScanCodes::ALTERASE),
		SYSREQ = MGL_SCANCODE_TO_KEYCODE(ScanCodes::SYSREQ),
		CANCEL = MGL_SCANCODE_TO_KEYCODE(ScanCodes::CANCEL),
		CLEAR = MGL_SCANCODE_TO_KEYCODE(ScanCodes::CLEAR),
		PRIOR = MGL_SCANCODE_TO_KEYCODE(ScanCodes::PRIOR),
		RETURN2 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::RETURN2),
		SEPARATOR = MGL_SCANCODE_TO_KEYCODE(ScanCodes::SEPARATOR),
		OUT = MGL_SCANCODE_TO_KEYCODE(ScanCodes::OUT),
		OPER = MGL_SCANCODE_TO_KEYCODE(ScanCodes::OPER),
		CLEARAGAIN = MGL_SCANCODE_TO_KEYCODE(ScanCodes::CLEARAGAIN),
		CRSEL = MGL_SCANCODE_TO_KEYCODE(ScanCodes::CRSEL),
		EXSEL = MGL_SCANCODE_TO_KEYCODE(ScanCodes::EXSEL),

		KP_00 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_00),
		KP_000 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_000),
		THOUSANDSSEPARATOR = MGL_SCANCODE_TO_KEYCODE(ScanCodes::THOUSANDSSEPARATOR),
		DECIMALSEPARATOR = MGL_SCANCODE_TO_KEYCODE(ScanCodes::DECIMALSEPARATOR),
		CURRENCYUNIT = MGL_SCANCODE_TO_KEYCODE(ScanCodes::CURRENCYUNIT),
		CURRENCYSUBUNIT = MGL_SCANCODE_TO_KEYCODE(ScanCodes::CURRENCYSUBUNIT),
		KP_LEFTPAREN = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_LEFTPAREN),
		KP_RIGHTPAREN = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_RIGHTPAREN),
		KP_LEFTBRACE = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_LEFTBRACE),
		KP_RIGHTBRACE = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_RIGHTBRACE),
		KP_TAB = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_TAB),
		KP_BACKSPACE = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_BACKSPACE),
		KP_A = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_A),
		KP_B = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_B),
		KP_C = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_C),
		KP_D = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_D),
		KP_E = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_E),
		KP_F = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_F),
		KP_XOR = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_XOR),
		KP_POWER = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_POWER),
		KP_PERCENT = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_PERCENT),
		KP_LESS = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_LESS),
		KP_GREATER = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_GREATER),
		KP_AMPERSAND = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_AMPERSAND),
		KP_DBLAMPERSAND =
		MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_DBLAMPERSAND),
		KP_VERTICALBAR =
		MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_VERTICALBAR),
		KP_DBLVERTICALBAR =
		MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_DBLVERTICALBAR),
		KP_COLON = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_COLON),
		KP_HASH = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_HASH),
		KP_SPACE = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_SPACE),
		KP_AT = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_AT),
		KP_EXCLAM = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_EXCLAM),
		KP_MEMSTORE = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_MEMSTORE),
		KP_MEMRECALL = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_MEMRECALL),
		KP_MEMCLEAR = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_MEMCLEAR),
		KP_MEMADD = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_MEMADD),
		KP_MEMSUBTRACT =
		MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_MEMSUBTRACT),
		KP_MEMMULTIPLY =
		MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_MEMMULTIPLY),
		KP_MEMDIVIDE = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_MEMDIVIDE),
		KP_PLUSMINUS = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_PLUSMINUS),
		KP_CLEAR = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_CLEAR),
		KP_CLEARENTRY = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_CLEARENTRY),
		KP_BINARY = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_BINARY),
		KP_OCTAL = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_OCTAL),
		KP_DECIMAL = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_DECIMAL),
		KP_HEXADECIMAL =
		MGL_SCANCODE_TO_KEYCODE(ScanCodes::KP_HEXADECIMAL),

		LCTRL = MGL_SCANCODE_TO_KEYCODE(ScanCodes::LCTRL),
		LSHIFT = MGL_SCANCODE_TO_KEYCODE(ScanCodes::LSHIFT),
		LALT = MGL_SCANCODE_TO_KEYCODE(ScanCodes::LALT),
		LGUI = MGL_SCANCODE_TO_KEYCODE(ScanCodes::LGUI),
		RCTRL = MGL_SCANCODE_TO_KEYCODE(ScanCodes::RCTRL),
		RSHIFT = MGL_SCANCODE_TO_KEYCODE(ScanCodes::RSHIFT),
		RALT = MGL_SCANCODE_TO_KEYCODE(ScanCodes::RALT),
		RGUI = MGL_SCANCODE_TO_KEYCODE(ScanCodes::RGUI),

		MODE = MGL_SCANCODE_TO_KEYCODE(ScanCodes::MODE),

		AUDIONEXT = MGL_SCANCODE_TO_KEYCODE(ScanCodes::AUDIONEXT),
		AUDIOPREV = MGL_SCANCODE_TO_KEYCODE(ScanCodes::AUDIOPREV),
		AUDIOSTOP = MGL_SCANCODE_TO_KEYCODE(ScanCodes::AUDIOSTOP),
		AUDIOPLAY = MGL_SCANCODE_TO_KEYCODE(ScanCodes::AUDIOPLAY),
		AUDIOMUTE = MGL_SCANCODE_TO_KEYCODE(ScanCodes::AUDIOMUTE),
		MEDIASELECT = MGL_SCANCODE_TO_KEYCODE(ScanCodes::MEDIASELECT),
		WWW = MGL_SCANCODE_TO_KEYCODE(ScanCodes::WWW),
		MAIL = MGL_SCANCODE_TO_KEYCODE(ScanCodes::MAIL),
		CALCULATOR = MGL_SCANCODE_TO_KEYCODE(ScanCodes::CALCULATOR),
		COMPUTER = MGL_SCANCODE_TO_KEYCODE(ScanCodes::COMPUTER),
		AC_SEARCH = MGL_SCANCODE_TO_KEYCODE(ScanCodes::AC_SEARCH),
		AC_HOME = MGL_SCANCODE_TO_KEYCODE(ScanCodes::AC_HOME),
		AC_BACK = MGL_SCANCODE_TO_KEYCODE(ScanCodes::AC_BACK),
		AC_FORWARD = MGL_SCANCODE_TO_KEYCODE(ScanCodes::AC_FORWARD),
		AC_STOP = MGL_SCANCODE_TO_KEYCODE(ScanCodes::AC_STOP),
		AC_REFRESH = MGL_SCANCODE_TO_KEYCODE(ScanCodes::AC_REFRESH),
		AC_BOOKMARKS = MGL_SCANCODE_TO_KEYCODE(ScanCodes::AC_BOOKMARKS),

		BRIGHTNESSDOWN = MGL_SCANCODE_TO_KEYCODE(ScanCodes::BRIGHTNESSDOWN),
		BRIGHTNESSUP = MGL_SCANCODE_TO_KEYCODE(ScanCodes::BRIGHTNESSUP),
		DISPLAYSWITCH = MGL_SCANCODE_TO_KEYCODE(ScanCodes::DISPLAYSWITCH),
		KBDILLUMTOGGLE = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KBDILLUMTOGGLE),
		KBDILLUMDOWN = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KBDILLUMDOWN),
		KBDILLUMUP = MGL_SCANCODE_TO_KEYCODE(ScanCodes::KBDILLUMUP),
		EJECT = MGL_SCANCODE_TO_KEYCODE(ScanCodes::EJECT),
		SLEEP = MGL_SCANCODE_TO_KEYCODE(ScanCodes::SLEEP),
		APP1 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::APP1),
		APP2 = MGL_SCANCODE_TO_KEYCODE(ScanCodes::APP2),

		AUDIOREWIND = MGL_SCANCODE_TO_KEYCODE(ScanCodes::AUDIOREWIND),
		AUDIOFASTFORWARD = MGL_SCANCODE_TO_KEYCODE(ScanCodes::AUDIOFASTFORWARD)
	};
}
