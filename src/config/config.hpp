#pragma once

#include "USB.h"
#include "USBHIDConsumerControl.h"
#include "USBHIDKeyboard.h"

#include "../keycodes/keycodes.hpp"

#include <vector>

// A2 -> A0  |  A2 -> A1  |  A3 -> A0
// A4 -> A0  |        A4 -> A1

#define MATRIX_COLUMNS { A0, A1 };
#define MATRIX_ROWS { A2, A3, A4 };

#define NETWORK_SSID ""
#define NETWORK_PASS ""

#define ENCODER_PIN_A 2U
#define ENCODER_PIN_B 3U


#define KEYMAP {{KC_Q, KC_W, KC_E, KC_R, KC_S}};
