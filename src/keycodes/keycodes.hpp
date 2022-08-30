
#pragma once

enum keycode_type : uint8_t {
    KT_UNKNOWN          = 0,
    KT_DEFAULT          = 1,
    KT_MACRO            = 2,
    KT_FUNCTION         = 3,
    KT_MEDIA            = 4,
    KT_RGB              = 5,
    KT_MOUSE            = 6,
    KT_LAYER_HOLD       = 7,
    KT_LAYER_SWITCH     = 8,
    KT_LAYER_TOGGLE     = 9,
};

#define TO_DEFAULT(key) (key & KEY_DEFAULT_MIN)
#define TO_MACRO(key) (key & KEY_MACRO_MIN)
#define TO_FUNCTION(key) (key & KEY_FUNCTION_MIN)
#define TO_MEDIA(key) (key & KEY_MEDIA_MIN)
#define TO_RGB(key) (key & KEY_RGB_MIN)
#define TO_MOUSE(key) (key & KEY_MOUSE_MIN)
#define TO_LAYER_HOLD(key) (key & KEY_LAYER_HOLD_MIN)
#define TO_LAYER_SWITCH(key) (key & KEY_LAYER_SWITCH_MIN)
#define TO_LAYER_TOGGLE(key) (key & KEY_LAYER_TOGGLE_MIN)

#define FROM_DEFAULT(key) (key ^ KEY_DEFAULT_MIN)
#define FROM_MACRO(key) (key ^ KEY_MACRO_MIN)
#define FROM_FUNCTION(key) (key ^ KEY_FUNCTION_MIN)
#define FROM_MEDIA(key) (key ^ KEY_MEDIA_MIN)
#define FROM_RGB(key) (key ^ KEY_RGB_MIN)
#define FROM_MOUSE(key) (key ^ KEY_MOUSE_MIN)
#define FROM_LAYER_HOLD(key) (key ^ KEY_LAYER_HOLD_MIN)
#define FROM_LAYER_SWITCH(key) (key ^ KEY_LAYER_SWITCH_MIN)
#define FROM_LAYER_TOGGLE(key) (key ^ KEY_LAYER_TOGGLE_MIN)

#define IS_DEFAULT(key) (key >= KEY_DEFAULT_MIN && key <= KEY_DEFAULT_MAX)
#define IS_MACRO(key) (key >= KEY_MACRO_MIN && key <= KEY_MACRO_MAX)
#define IS_FUNCTION(key) (key >= KEY_FUNCTION_MIN && key <= KEY_FUNCTION_MAX)
#define IS_MEDIA(key) (key >= KEY_MEDIA_MIN && key <= KEY_MEDIA_MAX)
#define IS_RGB(key) (key >= KEY_RGB_MIN && key <= KEY_RGB_MAX)
#define IS_MOUSE(key) (key >= KEY_MOUSE_MIN && key <= KEY_MOUSE_MAX)
#define IS_LAYER_HOLD(key) (key >= KEY_LAYER_HOLD_MIN && key <= KEY_LAYER_HOLD_MAX)
#define IS_LAYER_SWITCH(key) (key >= KEY_LAYER_SWITCH_MIN && key <= KEY_LAYER_SWITCH_MAX)
#define IS_LAYER_TOGGLE(key) (key >= KEY_LAYER_TOGGLE_MIN && key <= KEY_LAYER_TOGGLE_MAX)

#define IS_LAYER(key) (IS_LAYER_HOLD(key) || IS_LAYER_SWITCH(key) || IS_LAYER_TOGGLE(key))

#define SWITCH_DEFAULT KEY_DEFAULT_MIN...KEY_DEFAULT_MAX
#define SWITCH_MACRO KEY_MACRO_MIN...KEY_MACRO_MAX
#define SWITCH_FUNCTION KEY_FUNCTION_MIN...KEY_FUNCTION_MAX
#define SWITCH_MEDIA KEY_MEDIA_MIN...KEY_MEDIA_MAX
#define SWITCH_RGB KEY_RGB_MIN...KEY_RGB_MAX
#define SWITCH_MOUSE KEY_MOUSE_MIN...KEY_MOUSE_MAX
#define SWITCH_LAYER_HOLD KEY_LAYER_HOLD_MIN...KEY_LAYER_HOLD_MAX
#define SWITCH_LAYER_SWITCH KEY_LAYER_SWITCH_MIN...KEY_LAYER_SWITCH_MAX
#define SWITCH_LAYER_TOGGLE KEY_LAYER_TOGGLE_MIN...KEY_LAYER_TOGGLE_MAX

#define SWITCH_LAYER KEY_LAYER_HOLD_MIN...KEY_LAYER_TOGGLE_MAX

enum control_keycodes : uint32_t {
    KEY_DEFAULT_MIN             = 0x0000 << 16,
    KEY_DEFAULT_MAX             = 0x00FF << 16,
    KEY_MACRO_MIN               = 0x0100 << 16,
    KEY_MACRO_MAX               = 0x01FF << 16,
    KEY_FUNCTION_MIN            = 0x0200 << 16,
    KEY_FUNCTION_MAX            = 0x02FF << 16,
    KEY_MEDIA_MIN               = 0x0300 << 16,
    KEY_MEDIA_MAX               = 0x03FF << 16,
    KEY_RGB_MIN                 = 0x0400 << 16,
    KEY_RGB_MAX                 = 0x04FF << 16,
    KEY_MOUSE_MIN               = 0x0500 << 16,
    KEY_MOUSE_MAX               = 0x05FF << 16,
    KEY_LAYER_HOLD_MIN          = 0x0600 << 16,
    KEY_LAYER_HOLD_MAX          = 0x06FF << 16,
    KEY_LAYER_SWITCH_MIN        = 0x0700 << 16,
    KEY_LAYER_SWITCH_MAX        = 0x07FF << 16,
    KEY_LAYER_TOGGLE_MIN        = 0x0800 << 16,
    KEY_LAYER_TOGGLE_MAX        = 0x08FF << 16,
    KC_EXTEND                   = 0x0900 << 16,
};

#define LAYER_HOLD(layer)   (KEY_LAYER_HOLD_MIN   | ((layer) & 0xF << 4))
#define LAYER_SWITCH(layer) (KEY_LAYER_SWITCH_MIN | ((layer) & 0xF << 4))
#define LAYER_TOGGLE(layer) (KEY_LAYER_TOGGLE_MIN | ((layer) & 0xF << 4))

#define HL(layer) LAYER_HOLD(layer)
#define SL(layer) LAYER_SWITCH(layer)
#define TL(layer) LAYER_TOGGLE(layer)

#define MOD_LCTL 0x01
#define MOD_LSFT 0x02
#define MOD_LALT 0x04
#define MOD_LGUI 0x08
#define MOD_RCTL 0x10
#define MOD_RSFT 0x20
#define MOD_RALT 0x40
#define MOD_RGUI 0x80

#define SELECT_MODS(keycode) (keycode >> 24)
#define STRIP_MODS(keycode) (keycode & ~(0xFF << 24))
#define APPLY_MODS(mods, keycode) (mods << 24 | keycode)

#define LC(keycode) APPLY_MODS(MOD_LCTL, keycode)
#define LS(keycode) APPLY_MODS(MOD_LSFT, keycode)
#define LA(keycode) APPLY_MODS(MOD_LALT, keycode)
#define LG(keycode) APPLY_MODS(MOD_LGUI, keycode)
#define RC(keycode) APPLY_MODS(MOD_RCTL, keycode)
#define RS(keycode) APPLY_MODS(MOD_RSFT, keycode)
#define RA(keycode) APPLY_MODS(MOD_RALT, keycode)
#define RG(keycode) APPLY_MODS(MOD_RGUI, keycode)

enum hid_keyboard_keypad_usage : uint32_t {
    ____ = TO_DEFAULT(0x00),
    KC_NO = TO_DEFAULT(0x00),
    KC_ROLL_OVER, // 0x01
    KC_POST_FAIL, // 0x02
    KC_UNDEFINED, // 0x03
    KC_A, // 0x04
    KC_B, // 0x05
    KC_C, // 0x06
    KC_D, // 0x07
    KC_E, // 0x08
    KC_F, // 0x09
    KC_G, // 0x0A
    KC_H, // 0x0B 
    KC_I, // 0x0C
    KC_J, // 0x0D
    KC_K, // 0x0E
    KC_L, // 0x0F
    KC_M, // 0x10
    KC_N, // 0x11
    KC_O, // 0x12
    KC_P, // 0x13
    KC_Q, // 0x14
    KC_R, // 0x15
    KC_S, // 0x16
    KC_T, // 0x17
    KC_U, // 0x18
    KC_V, // 0x19
    KC_W, // 0x1A
    KC_X, // 0x1B
    KC_Y, // 0x1C
    KC_Z, // 0x1D
    KC_1, // 0x1E
    KC_2, // 0x1F
    KC_3, // 0x20
    KC_4, // 0x21
    KC_5, // 0x22
    KC_6, // 0x23
    KC_7, // 0x24
    KC_8, // 0x25
    KC_9, // 0x26
    KC_0, // 0x27
    KC_ENTER, // 0x28
    KC_ESCAPE, // 0x29
    KC_BACKSPACE, // 0x2A
    KC_TAB, // 0x2B
    KC_SPACE, // 0x2C
    KC_MINUS, // 0x2D
    KC_EQUAL, // 0x2E
    KC_LEFT_BRACKET, // 0x2F
    KC_RIGHT_BRACKET, // 0x30
    KC_BACKSLASH, // 0x31
    KC_NONUS_HASH, // 0x32
    KC_SEMICOLON, // 0x33
    KC_QUOTE, // 0x34
    KC_GRAVE, // 0x35
    KC_COMMA, // 0x36
    KC_DOT, // 0x37
    KC_SLASH, // 0x38
    KC_CAPS_LOCK, // 0x39
    KC_F1, // 0x3A
    KC_F2, // 0x3B
    KC_F3, // 0x3C
    KC_F4, // 0x3D
    KC_F5, // 0x3E
    KC_F6, // 0x3F
    KC_F7, // 0x40
    KC_F8, // 0x41
    KC_F9, // 0x42
    KC_F10, // 0x43
    KC_F11, // 0x44
    KC_F12, // 0x45
    KC_PRINT_SCREEN, // 0x46
    KC_SCROLL_LOCK, // 0x47
    KC_PAUSE, // 0x48
    KC_INSERT, // 0x49
    KC_HOME, // 0x4A
    KC_PAGE_UP, // 0x4B
    KC_DELETE, // 0x4C
    KC_END, // 0x4D
    KC_PAGE_DOWN, // 0x4E
    KC_RIGHT, // 0x4F
    KC_LEFT, // 0x50
    KC_DOWN, // 0x51
    KC_UP, // 0x52
    KC_NUM_LOCK, // 0x53
    KC_KP_SLASH, // 0x54
    KC_KP_ASTERISK, // 0x55
    KC_KP_MINUS, // 0x56
    KC_KP_PLUS, // 0x57
    KC_KP_ENTER, // 0x58
    KC_KP_1, // 0x59
    KC_KP_2, // 0x5A
    KC_KP_3, // 0x5B
    KC_KP_4, // 0x5C
    KC_KP_5, // 0x5D
    KC_KP_6,
    KC_KP_7,
    KC_KP_8,
    KC_KP_9,
    KC_KP_0,
    KC_KP_DOT,
    KC_NONUS_BACKSLASH,
    KC_APPLICATION,
    KC_KB_POWER,
    KC_KP_EQUAL,
    KC_F13,
    KC_F14,
    KC_F15,
    KC_F16,
    KC_F17,
    KC_F18,
    KC_F19,
    KC_F20,
    KC_F21,
    KC_F22,
    KC_F23,
    KC_F24,
    KC_EXECUTE,
    KC_HELP,
    KC_MENU,
    KC_SELECT,
    KC_STOP,
    KC_AGAIN,
    KC_UNDO,
    KC_CUT,
    KC_COPY,
    KC_PASTE,
    KC_FIND,
    KC_KB_MUTE,
    KC_KB_VOLUME_UP,
    KC_KB_VOLUME_DOWN,
    KC_LOCKING_CAPS_LOCK,
    KC_LOCKING_NUM_LOCK,
    KC_LOCKING_SCROLL_LOCK,
    KC_KP_COMMA,
    KC_KP_EQUAL_AS400,
    KC_INTERNATIONAL_1,
    KC_INTERNATIONAL_2,
    KC_INTERNATIONAL_3,
    KC_INTERNATIONAL_4,
    KC_INTERNATIONAL_5,
    KC_INTERNATIONAL_6,
    KC_INTERNATIONAL_7,
    KC_INTERNATIONAL_8,
    KC_INTERNATIONAL_9,
    KC_LANGUAGE_1,
    KC_LANGUAGE_2,
    KC_LANGUAGE_3,
    KC_LANGUAGE_4,
    KC_LANGUAGE_5,
    KC_LANGUAGE_6,
    KC_LANGUAGE_7,
    KC_LANGUAGE_8,
    KC_LANGUAGE_9,
    KC_ALTERNATE_ERASE,
    KC_SYSTEM_REQUEST,
    KC_CANCEL,
    KC_CLEAR,
    KC_PRIOR,
    KC_RETURN,
    KC_SEPARATOR,
    KC_OUT,
    KC_OPER,
    KC_CLEAR_AGAIN,
    KC_CRSEL,
    KC_EXSEL,

    KC_KP_00 = TO_DEFAULT(0xB0),
    KC_KP_000,
    KC_THOUSANDS_SEPARATOR,
    KC_DECIMAL_SEPARATOR,
    KC_CURRENCY_UNIT,
    KC_CURRENCY_SUB_UNIT,
    KC_KP_LEFT_PAREN,
    KC_KP_RIGHT_PAREN,
    KC_KP_LEFT_BRACE,
    KC_KP_RIGHT_BRACE,
    KC_KP_TAB,
    KC_KP_BACKSPACE,
    KC_KP_A,
    KC_KP_B,
    KC_KP_C,
    KC_KP_D,
    KC_KP_E,
    KC_KP_F,
    KC_KP_XOR,
    KC_KP_HAT,
    KC_KP_PERCENT,
    KC_KP_LESS,
    KC_KP_GREATER,
    KC_KP_AMPERSAND,
    KC_KP_DBLAMPERSAND,
    KC_KP_VERTICAL_BAR,
    KC_KP_DBLVERTICAL_BAR,
    KC_KP_COLON,
    KC_KP_HASH,
    KC_KP_SPACE,
    KC_KP_AT,
    KC_KP_EXCLAM,
    KC_KP_MEM_STORE,
    KC_KP_MEM_RECALL,
    KC_KP_MEM_CLEAR,
    KC_KP_MEM_ADD,
    KC_KP_MEM_SUBTRACT,
    KC_KP_MEM_MULTIPLY,
    KC_KP_MEM_DIVIDE,
    KC_KP_PLUS_MINUS,
    KC_KP_CLEAR,
    KC_KP_CLEAR_ENTRY,
    KC_KP_BINARY,
    KC_KP_OCTAL,
    KC_KP_DECIMAL,
    KC_KP_HEXADECIMAL,

    KC_LEFT_CTRL = TO_DEFAULT(0xE0),
    KC_LEFT_SHIFT,
    KC_LEFT_ALT,
    KC_LEFT_GUI,
    KC_RIGHT_CTRL,
    KC_RIGHT_SHIFT,
    KC_RIGHT_ALT,
    KC_RIGHT_GUI
};

enum media_keycodes : uint32_t {
    KC_MEDIA_POWER                             = TO_MEDIA(0x0030),
    KC_MEDIA_RESET                             = TO_MEDIA(0x0031),
    KC_MEDIA_SLEEP                             = TO_MEDIA(0x0032),

// Screen Brightness
    KC_MEDIA_BRIGHTNESS_INCREMENT              = TO_MEDIA(0x006F),
    KC_MEDIA_BRIGHTNESS_DECREMENT              = TO_MEDIA(0x0070),

// These HID usages operate only on mobile systems (battery powered) and
// require Windows 8 (build 8302 or greater).
    KC_MEDIA_WIRELESS_RADIO_CONTROLS           = TO_MEDIA(0x000C),
    KC_MEDIA_WIRELESS_RADIO_BUTTONS            = TO_MEDIA(0x00C6),
    KC_MEDIA_WIRELESS_RADIO_LED                = TO_MEDIA(0x00C7),
    KC_MEDIA_WIRELESS_RADIO_SLIDER_SWITCH      = TO_MEDIA(0x00C8),

// Media Control
    KC_MEDIA_PLAY_PAUSE                        = TO_MEDIA(0x00CD),
    KC_MEDIA_SCAN_NEXT                         = TO_MEDIA(0x00B5),
    KC_MEDIA_SCAN_PREVIOUS                     = TO_MEDIA(0x00B6),
    KC_MEDIA_STOP                              = TO_MEDIA(0x00B7),
    KC_MEDIA_VOLUME                            = TO_MEDIA(0x00E0),
    KC_MEDIA_MUTE                              = TO_MEDIA(0x00E2),
    KC_MEDIA_BASS                              = TO_MEDIA(0x00E3),
    KC_MEDIA_TREBLE                            = TO_MEDIA(0x00E4),
    KC_MEDIA_BASS_BOOST                        = TO_MEDIA(0x00E5),
    KC_MEDIA_VOLUME_INCREMENT                  = TO_MEDIA(0x00E9),
    KC_MEDIA_VOLUME_DECREMENT                  = TO_MEDIA(0x00EA),
    KC_MEDIA_BASS_INCREMENT                    = TO_MEDIA(0x0152),
    KC_MEDIA_BASS_DECREMENT                    = TO_MEDIA(0x0153),
    KC_MEDIA_TREBLE_INCREMENT                  = TO_MEDIA(0x0154),
    KC_MEDIA_TREBLE_DECREMENT                  = TO_MEDIA(0x0155),

// Application Launcher
    KC_MEDIA_CONFIGURATION                     = TO_MEDIA(0x0183),
    KC_MEDIA_EMAIL_READER                      = TO_MEDIA(0x018A),
    KC_MEDIA_CALCULATOR                        = TO_MEDIA(0x0192),
    KC_MEDIA_LOCAL_BROWSER                     = TO_MEDIA(0x0194),

// Browser/Explorer Specific
    KC_MEDIA_SEARCH                            = TO_MEDIA(0x0221),
    KC_MEDIA_HOME                              = TO_MEDIA(0x0223),
    KC_MEDIA_BACK                              = TO_MEDIA(0x0224),
    KC_MEDIA_FORWARD                           = TO_MEDIA(0x0225),
    KC_MEDIA_BR_STOP                           = TO_MEDIA(0x0226),
    KC_MEDIA_REFRESH                           = TO_MEDIA(0x0227),
    KC_MEDIA_BOOKMARKS                         = TO_MEDIA(0x022A),

// Mouse Horizontal scroll
    KC_MEDIA_PAN                               = TO_MEDIA(0x0238),
};

enum mouse_keycodes : uint32_t {
    KC_MS_UP = TO_MOUSE(0xED),
    KC_MS_DOWN,
    KC_MS_LEFT,
    KC_MS_RIGHT,
    KC_MS_BTN1,
    KC_MS_BTN2,
    KC_MS_BTN3,
    KC_MS_BTN4,
    KC_MS_BTN5,
    KC_MS_BTN6,
    KC_MS_BTN7,
    KC_MS_BTN8,
    KC_MS_WH_UP,
    KC_MS_WH_DOWN,
    KC_MS_WH_LEFT,
    KC_MS_WH_RIGHT,
    KC_MS_ACCEL0,
    KC_MS_ACCEL1,
    KC_MS_ACCEL2
};