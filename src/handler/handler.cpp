
#include "handler.hpp"

void keycode_handler(uint16_t keycode) {
    switch(keycode) {
        case KEY_MACRO_MIN...KEY_LAYER_TOGGLE_MAX:

            break;
        case KC_NO...KC_EXSEL:

            break;
        case KC_LEFT_CTRL...KC_RIGHT_GUI:

            break;
        case KC_SYSTEM_POWER...KC_BRIGHTNESS_DOWN:

            break;
        case KC_MS_UP...KC_MS_ACCEL2:

            break;
    }
}