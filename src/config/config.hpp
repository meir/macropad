#pragma once

#include "USB.h"
#include "USBHIDConsumerControl.h"
#include "USBHIDKeyboard.h"

#include "../keycodes/keycodes.hpp"

#include <vector>

// A2 -> A0  |  A2 -> A1  |  A3 -> A0
// A4 -> A0  |        A4 -> A1

// #define DEBUG

#define MATRIX_COLUMNS { A0, A1 };
#define MATRIX_ROWS { A2, A3, A4 };

#define ENCODER_PIN_A 12
#define ENCODER_PIN_B 13
#define ROTARY_DIVIDER 4

// Define default keymap, this will be able to be changed within the web interface eventually.
#define KEYMAP {\
    {KC_F13, KC_F14, KC_F15, ____, KC_F16, KC_F17},\
    {KC_F18, KC_F19, KC_F20, ____, KC_F21, KC_F22},\
    {KC_Q,   KC_W,   KC_E,   ____, KC_R,   KC_LEFT_CTRL},\
};

#define LAYER_NAMES {"F13-F17", "F18-F22", "League "}
#define LAYER_COLORS {0x7e2bcc, 0xd9276b, 0xebeb54}

// Network SSID and Password are required to launch the web server and give an ip.
#define NETWORK_SSID ""
#define NETWORK_PASS ""