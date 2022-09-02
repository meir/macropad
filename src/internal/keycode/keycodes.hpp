
#pragma once

#include <Arduino.h>
#include <vector>

enum keycode_type_t : uint8_t {
    T_DEFAULT           = 0x00,
    T_MOD               = 0x10,
    T_MEDIA             = 0x20,
    T_LAYER_TOGL        = 0x30,
    T_LAYER_HOLD        = 0x40,
    T_LAYER_SWAP        = 0x50,
    T_CUSTOM            = 0xF0,
};

#define KC(code, type) ((type << 8) | code)

#define HOLD(code) KC(code, T_LAYER_HOLD)
#define TOGL(code) KC(code, T_LAYER_TOGGLE)
#define TO(code) KC(code, T_LAYER_SWAP)

#define KC_CUSTOM KC(0, T_CUSTOM)

typedef uint16_t keycode_t;

struct keydata_t {
    uint8_t keycode;
    keycode_t key;
    keycode_type_t type;
};

struct methods_t {
    void (*press)(uint16_t keycode);
    void (*release)(uint16_t keycode);
    void (*press_raw)(uint8_t keycode);
    void (*release_raw)(uint8_t keycode);
    void (*print)(String str);
    void (*println)(String str);
    void (*flush)();

    std::vector<keycode_t> (*get_layer_keys)(uint8_t index);
    String (*get_layer_name)(uint8_t index);
    uint32_t (*get_layer_color)(uint8_t index);
};

struct layer_t {
    std::vector<keycode_t> (*get_layer_keys)(uint8_t layer);
    std::vector<String> (*get_layer_names)(uint8_t layer);
    std::vector<uint32_t> (*get_layer_colors)(uint8_t layer);
    void (*set_layer)(uint8_t layer);
};

enum event_type_t : uint8_t {
    EVENT_KEY_UP = 0,
    EVENT_KEY_DOWN,
    EVENT_ENCODER_TICK,
    EVENT_DISPLAY_TICK,
};

struct event_t {
    event_type_t type;
    keydata_t keydata;
    uint8_t* layer;
    uint8_t layer_count;
    methods_t methods;
};

typedef std::vector<keycode_t> LAYER;
typedef std::vector<LAYER> KEYMAP;
typedef std::vector<String> LAYER_NAMES;
typedef std::vector<uint32_t> LAYER_COLORS;

/** weaks **/

void task_user_keycode(event_t event) __attribute__ ((weak));
void task_user_keycode_custom(event_t event) __attribute__ ((weak));
void task_user_encoder_tick(event_t event) __attribute__ ((weak));
void task_user_display_tick(event_t event) __attribute__ ((weak));

KEYMAP keymap(KEYMAP pref) __attribute__ ((weak));
LAYER_NAMES layer_names(LAYER_NAMES pref) __attribute__ ((weak));
LAYER_COLORS layer_colors(LAYER_COLORS pref) __attribute__ ((weak));

LAYER get_layer_keys(uint8_t index) __attribute__ ((weak));
String get_layer_name(uint8_t index) __attribute__ ((weak));
uint32_t get_layer_color(uint8_t index) __attribute__ ((weak));

void set_layer(uint8_t layer) __attribute__ ((weak));


enum keycodes : keycode_t {
    ____ = KC(0x00, T_DEFAULT),
    KC_NO = KC(0x00, T_DEFAULT),
    KC_ROLL_OVER,
    KC_POST_FAIL,
    KC_UNDEFINED,
    KC_A,
    KC_B,
    KC_C,
    KC_D,
    KC_E,
    KC_F,
    KC_G,
    KC_H,
    KC_I,
    KC_J,
    KC_K,
    KC_L,
    KC_M,
    KC_N,
    KC_O,
    KC_P,
    KC_Q, // 15
    KC_R,
    KC_S,
    KC_T,
    KC_U,
    KC_V,
    KC_W,
    KC_X,
    KC_Y,
    KC_Z,
    KC_1,
    KC_2,
    KC_3,
    KC_4,
    KC_5,
    KC_6,
    KC_7,
    KC_8,
    KC_9,
    KC_0,
    KC_ENTER,
    KC_ESCAPE,
    KC_BSPACE,
    KC_TAB,
    KC_SPACE,
    KC_MINUS,
    KC_EQUAL,
    KC_LBRACKET,
    KC_RBRACKET,
    KC_BSLASH,
    KC_NONUS_HASH,
    KC_SCOLON,
    KC_QUOTE,
    KC_GRAVE,
    KC_COMMA,
    KC_DOT,
    KC_SLASH,
    KC_CAPSLOCK,
    KC_F1,
    KC_F2,
    KC_F3,
    KC_F4,
    KC_F5,
    KC_F6,
    KC_F7,
    KC_F8,
    KC_F9,
    KC_F10,
    KC_F11,
    KC_F12,
    KC_PSCREEN,
    KC_SCROLLLOCK,
    KC_PAUSE,
    KC_INSERT,
    KC_HOME,
    KC_PGUP,
    KC_DELETE,
    KC_END,
    KC_PGDOWN,
    KC_RIGHT,
    KC_LEFT,
    KC_DOWN,
    KC_UP,
    KC_NUMLOCK,
    KC_KP_SLASH,
    KC_KP_ASTERISK,
    KC_KP_MINUS,
    KC_KP_PLUS,
    KC_KP_ENTER,
    KC_KP_1,
    KC_KP_2,
    KC_KP_3,
    KC_KP_4,
    KC_KP_5,
    KC_KP_6,
    KC_KP_7,
    KC_KP_8,
    KC_KP_9,
    KC_KP_0,
    KC_KP_DOT,
    KC_NONUS_BSLASH,
    KC_APPLICATION,
    KC_POWER,
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
};

enum modifier_keycodes : keycode_t {
    KC_LCTRL = KC(0xE0, T_MOD),
    KC_LSHIFT,
    KC_LALT,
    KC_LGUI,
    KC_RCTRL,
    KC_RSHIFT,
    KC_RALT,
    KC_RGUI,
};

#define ADD_MOD(key, mod) ( (keycode_t) (key | (((mod + 1) ^ 0xE0) << 8)))
#define MOD(key) ((((key >> 8) ^ ((key >> 12) << 4)) - 1) | 0xE0)
#define HAS_MOD(key) ((key >> 8) ^ ((key >> 12) << 4) != 0)

#define LCTRL(key) ADD_MOD(key, KC_LCTRL)
#define LSHIFT(key) ADD_MOD(key, KC_LSHIFT)
#define LALT(key) ADD_MOD(key, KC_LALT)
#define LGUI(key) ADD_MOD(key, KC_LGUI)
#define RCTRL(key) ADD_MOD(key, KC_RCTRL)
#define RSHIFT(key) ADD_MOD(key, KC_RSHIFT)
#define RALT(key) ADD_MOD(key, KC_RALT)
#define RGUI(key) ADD_MOD(key, KC_RGUI)

enum system_keycodes : keycode_t {
    KC_SYSTEM_POWER         = KC(0x30, T_MEDIA),
    KC_SYSTEM_SLEEP,
    KC_SYSTEM_WAKE,

    KC_BRIGHTNESS_UP        = KC(0x6F, T_MEDIA),
    KC_BRIGHTNESS_DOWN,

    KC_PLAY_PAUSE           = KC(0xCD, T_MEDIA),
    KC_NEXT_TRACK           = KC(0xB5, T_MEDIA),
    KC_PREV_TRACK           = KC(0xB6, T_MEDIA),
    KC_MEDIA_STOP           = KC(0xB7, T_MEDIA),
    KC_VOLUME               = KC(0xE0, T_MEDIA),
    KC_MUTE                 = KC(0xE2, T_MEDIA),
    KC_VOLUME_INCREMENT     = KC(0xE9, T_MEDIA),
    KC_VOLUME_DECREMENT     = KC(0xEA, T_MEDIA),
};