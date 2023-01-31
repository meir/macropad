
#pragma once

#include "../internal/keycode/keycodes.hpp"
#include "../internal/graphics/graphics.hpp"

#define MATRIX_COLUMNS { A0, A1 };
#define MATRIX_ROWS { A2, A3, A4 };

#define DISPLAY_WIDTH 135
#define DISPLAY_HEIGHT 240
#define DISPLAY_ROTATION 2

#define DISPLAY_ANIMATION_ENABLED
#define DISPLAY_ANIMATION_FPS 8

#define NEOPIXEL_PIN PIN_NEOPIXEL 
#define NUMPIXELS 1

#define NEOPIXEL_ENABLED
#define ENCODER_ENABLED
#define DISPLAY_ENABLED
#define WEBSITE_ENABLED

#include "./wifi.hpp"

#define NETWORK_ENABLED

#define NETWORK_SSID WIFI_SSID
#define NETWORK_PASS WIFI_PASS
