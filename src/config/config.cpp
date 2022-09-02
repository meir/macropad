
#include "config.hpp"

#include <Encoder.h>

#define ENCODER_PIN_A 12
#define ENCODER_PIN_B 13
#define ROTARY_DIVIDER 4

Encoder encoder(ENCODER_PIN_A, ENCODER_PIN_B);

enum custom_keys : keycode_t {
    MORNING = KC_CUSTOM,
    UNDO,
    REDO,
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
            ____, KC_R,   KC_LCTRL
        },
        {
            KC_PREV_TRACK, KC_PLAY_PAUSE, KC_NEXT_TRACK, 
            ____, LCTRL(KC_Z), LCTRL(KC_Y)
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

void task_user_keycode_custom(event_t event) {
    switch(event.keydata.key) {
        case MORNING:
            if(event.type != EVENT_KEY_DOWN) return;
            event.methods.println("morning");
            return;
    }
};

void task_user_encoder_tick(event_t event) {
    uint16_t encoder_value = encoder.read();
    uint16_t layer_change = (encoder_value / ROTARY_DIVIDER) % event.layer_count;
    (*event.layer) = layer_change;
}

void task_user_display_tick(event_t event) {
    get_canvas()->setTextColor(event.methods.get_layer_color(*event.layer));
    get_canvas()->setTextSize(2);
    get_canvas()->println(event.methods.get_layer_name(*event.layer));
    gfx_set_led(0, event.methods.get_layer_color(*event.layer));
}