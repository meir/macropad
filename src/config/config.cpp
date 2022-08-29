
#include "config.hpp"

Encoder encoder(ENCODER_PIN_A, ENCODER_PIN_B);

void task_user_keycode(event_t event) {
    switch(event.keycode) {
        case KC_CTRL_Z:
            {
                switch(event.type) {
                    case KEY_DOWN:
                        {
                            event.keyboard.pressRaw(KC_LEFT_CTRL);
                            event.keyboard.pressRaw(KC_Z);
                            break;
                        }
                    case KEY_UP:
                        {
                            event.keyboard.releaseRaw(KC_Z);
                            event.keyboard.releaseRaw(KC_LEFT_CTRL);
                            break;
                        }
                }
                break;
            }
        case KC_CTRL_Y:
            {
                switch(event.type) {
                    case KEY_DOWN:
                        {
                            event.keyboard.pressRaw(KC_LEFT_CTRL);
                            event.keyboard.pressRaw(KC_Y);
                            break;
                        }
                    case KEY_UP:
                        {
                            event.keyboard.releaseRaw(KC_Y);
                            event.keyboard.releaseRaw(KC_LEFT_CTRL);
                            break;
                        }
                }
                break;
            }
    }
};

void task_user_encoder_tick(event_t event) {
    int encoderValue = encoder.read();
    encoderValue = encoderValue < 0 ? -encoderValue : encoderValue;
    uint32_t activeLayer = (encoderValue / ROTARY_DIVIDER) % event.layers;
    (*event.layer) = activeLayer;
}

void task_user_display_tick(event_t event) {
    gfx_println("Layer: \n" + event.layername);
    led_setColor(event.layercolor);
}
