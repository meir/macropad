
#pragma once

#include <Encoder.h>
#include "../handler/handler.hpp"
#include "../keycodes/keycodes.hpp"

#include "../graphics/graphics.hpp"

// A2 -> A0  |  A2 -> A1  |  A3 -> A0
// A4 -> A0  |        A4 -> A1

// #define DEBUG

#define MATRIX_COLUMNS { A0, A1 };
#define MATRIX_ROWS { A2, A3, A4 };

#define ENCODER_ENABLE
#define DISPLAY_ENABLE

enum custom_keys : uint32_t {
    KC_CTRL_Z = KEY_CUSTOM_START,
    KC_CTRL_Y
};

// Define default keymap, this will be able to be changed within the web interface eventually.
#define KEYMAP {\
    {KC_F13, KC_F14, KC_F15, KC_NO, KC_F16, KC_F17},\
    {KC_F18, KC_F19, KC_F20, KC_NO, KC_F21, KC_F22},\
    {KC_Q,   KC_W,   KC_E,   KC_NO, KC_R,   KC_LEFT_CTRL},\
    {KC_MEDIA_SCAN_PREVIOUS, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_SCAN_NEXT, KC_NO, KC_CTRL_Z, KC_CTRL_Y},\
};

#define LAYER_NAMES {"F13-F17", "F18-F22", "League", "Media"}
#define LAYER_COLORS {0x7e2bcc, 0xd9276b, 0xebeb54}

// Network SSID and Password are required to launch the web server and give an ip.
#define NETWORK_SSID ""
#define NETWORK_PASS ""



// Custom defines

#define ENCODER_PIN_A 12
#define ENCODER_PIN_B 13
#define ROTARY_DIVIDER 4