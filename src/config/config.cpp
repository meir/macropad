
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
            ____, LC(KC_Z), LC(KC_Y)
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
            event.keyboard.println("Morning");
    }
};

void task_user_encoder_tick(event_t event) {
    uint32_t encoderValue = encoder.read();
    uint32_t activeLayer = (encoderValue / ROTARY_DIVIDER) % event.layers;
    (*event.layer) = activeLayer;
}

void task_user_display_tick(event_t event) {
    canvas().setTextColor(event.layercolor);
    gfx_println(" " + event.layername);
    led_setColor(event.layercolor);
}
