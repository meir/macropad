
#include "config.hpp"

#include <Encoder.h>

#define ENCODER_PIN_A 12
#define ENCODER_PIN_B 13
#define ROTARY_DIVIDER 4

Encoder encoder(ENCODER_PIN_A, ENCODER_PIN_B);

enum custom_keys : keycode_t {
    MORNING = KC_CUSTOM,
    KC_TOGGLE_NEOPIXEL,
    KC_TOGGLE_LAYER_INFO,
    KC_TOGGLE_BACKLIGHT,
    KC_TOGGLE_DISPLAY,
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
        {
            KC_TOGGLE_NEOPIXEL, KC_TOGGLE_LAYER_INFO, KC_TOGGLE_BACKLIGHT,
            ____, KC_TOGGLE_DISPLAY, ____
        }
    };
}

LAYER_NAMES layer_names(LAYER_NAMES pref) {
    if(pref.size() != 0) return pref;
    return {"F13-F17", "F18-F22", "League", "Media", "Morning", "Toggles"};
}

LAYER_COLORS layer_colors(LAYER_COLORS pref) {
    if(pref.size() != 0) return pref;
    return {0x7e2bcc, 0xd9276b, 0xebeb54, 0x2b2b2b, 0xffffff, 0x2b2b2b};
}

bool neopixel_enabled = true;
bool layerinfo_enabled = false;
bool backlight_enabled = false;
bool display_enabled = true;

void task_user_keycode_custom(event_t event) {
    switch(event.keydata.key) {
        case MORNING:
            if(event.type != EVENT_KEY_DOWN) return;
            event.methods.println("morning");
            return;
        case KC_TOGGLE_NEOPIXEL:
            if(event.type != EVENT_KEY_DOWN) return;
            neopixel_enabled = !neopixel_enabled;
            return;
        case KC_TOGGLE_LAYER_INFO:
            if(event.type != EVENT_KEY_DOWN) return;
            layerinfo_enabled = !layerinfo_enabled;
            return;
        case KC_TOGGLE_BACKLIGHT:
            if(event.type != EVENT_KEY_DOWN) return;
            backlight_enabled = !backlight_enabled;
            gfx_backlight(backlight_enabled);
            return;
        case KC_TOGGLE_DISPLAY:
            if(event.type != EVENT_KEY_DOWN) return;
            display_enabled = !display_enabled;
            gfx_display(display_enabled);
            return;
    }
};

void task_user_encoder_tick(event_t event) {
    uint8_t encoder_value = encoder.read();
    uint8_t layer_change = (encoder_value / ROTARY_DIVIDER) % event.layer_count;
    (*event.layer) = layer_change;
}

void task_user_display_tick(event_t event) {
    if(layerinfo_enabled) {
        get_canvas()->setTextSize(1);
        get_canvas()->setCursor(0, DISPLAY_HEIGHT - 24);
        uint8_t encoder_value = encoder.read();
        get_canvas()->println("{L: " + String((*event.layer), DEC) + ", R: " + String(encoder_value, DEC) + " }");
    }
    
    get_canvas()->setCursor(0, DISPLAY_HEIGHT - 16);
    get_canvas()->setTextSize(2);
    get_canvas()->println(event.methods.get_layer_name(*event.layer));

    if(neopixel_enabled) {
        gfx_set_led(0, event.methods.get_layer_color(*event.layer));
    } else {
        gfx_clear_leds();
    }
}