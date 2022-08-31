
#include "config.hpp"

#include <Encoder.h>

#define ENCODER_PIN_A 12
#define ENCODER_PIN_B 13
#define ROTARY_DIVIDER 4

Encoder encoder(ENCODER_PIN_A, ENCODER_PIN_B);

enum custom_keys : uint32_t {
    MORNING = KC_EXTEND,
};

KEYMAP keymap(KEYMAP pref) {
    if(pref.size() != 0) return pref;
    return {
        {
            KC_F13, KC_F14, KC_F15, 
            ____, KC_F16, KC_F17
        },
        {
            KC_F18, KC_F19, KC_F20, 
            ____, KC_F21, KC_F22
        },
        {
            KC_Q,   KC_W,   KC_E,   
            ____, KC_R,   KC_LEFT_CTRL
        },
        {
            KC_MEDIA_SCAN_PREVIOUS, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_SCAN_NEXT, 
            ____, KC_Z, KC_LEFT_GUI,
        },
        {
            MORNING, MORNING, MORNING, 
            ____, MORNING, MORNING
        },
    };
}

LAYER_NAMES layer_names(LAYER_NAMES pref) {
    if(pref.size() != 0) return pref;
    return {"F13-F17", "F18-F22", "League", "Media", "Morning"};
}

LAYER_COLORS layer_colors(LAYER_COLORS pref) {
    if(pref.size() != 0) return pref;
    return {0x7e2bcc, 0xd9276b, 0xebeb54, 0x2b2b2b, 0xffffff};
}

void task_user_keycode(event_t event) {
    switch(event.keycode) {
        case MORNING:
            if(event.type != KEY_DOWN) return;
            event.keyboard.println("morning");
            break;
    }
};

int16_t encoder_old_value = 0;

void task_user_encoder_tick(event_t event) {
    int16_t encoder_value = encoder.read();
   
    if(encoder_value == encoder_old_value) return;
    int16_t offset = (encoder_value - encoder_old_value);
    int16_t layer_change = (offset / ROTARY_DIVIDER) % event.layers;
    
    if(layer_change == 0) return;
    (*event.layer) += layer_change;
    encoder_old_value = encoder_value;
}

void task_user_display_tick(event_t event) {
    gfx_println(" " + event.layername);
    led_setColor(event.layercolor);
}
