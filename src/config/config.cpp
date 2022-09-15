
#include "config.hpp"

#include "ditto.cpp"

#include <Encoder.h>

#define ENCODER_PIN_A 12
#define ENCODER_PIN_B 13
#define ROTARY_DIVIDER 4

Encoder encoder(ENCODER_PIN_A, ENCODER_PIN_B);

enum custom_keys : keycode_t {
    KC_TOGGLE_NEOPIXEL = KC_CUSTOM,
    KC_TOGGLE_LAYER_INFO,
    KC_TOGGLE_BACKLIGHT,
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
            RCTRL(KC_F13), RCTRL(KC_F14), RCTRL(KC_F15),
            ____, RCTRL(KC_F16), RCTRL(KC_F17) 
        },
        {
            RCTRL(KC_F18), RCTRL(KC_F19), RCTRL(KC_F20),
            ____, RCTRL(KC_F21), RCTRL(KC_F22)
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
            KC_TOGGLE_NEOPIXEL, KC_TOGGLE_LAYER_INFO, KC_TOGGLE_BACKLIGHT,
            ____, ____, ____
        }
    };
}

LAYER_NAMES layer_names(LAYER_NAMES pref) {
    if(pref.size() != 0) return pref;
    return {
        "F13-F17", 
        "F18-F22",
        "CTL F13-F17",
        "CTL F18-F22", 
        "League", 
        "Media",  
        "Toggles"
    };
}

LAYER_COLORS layer_colors(LAYER_COLORS pref) {
    if(pref.size() != 0) return pref;
    return {
        0x7e2bcc, 
        0x7e2bcc, 
        0xd9276b, 
        0xd9276b,
        0xebeb54, 
        0x2b2b2b,  
        0x2b2b2b,
    };
}

bool neopixel_enabled = true;
bool layerinfo_enabled = false;
bool backlight_enabled = true;

void task_user_keycode_custom(event_t event) {
    switch(event.keydata.key) {
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
    }
};

void task_user_encoder_tick(event_t event) {
    uint8_t encoder_value = encoder.read();
    uint8_t layer_change = (encoder_value / ROTARY_DIVIDER) % event.layer_count;
    (*event.layer) = layer_change;
}

uint8_t current_frame = 0;

void task_user_display_tick(event_t event) {
    GFXcanvas16 *canvas = get_canvas();

    if(layerinfo_enabled) {
        canvas->setTextSize(1);
        LAYER l = event.methods.get_layer_keys((*event.layer));
        for(uint8_t i = 0; i < l.size(); i++) {
            canvas->println(String(l[i], HEX));
            canvas->println(String(HAS_MOD(l[i]), HEX) + " : " + String(MOD(l[i]), HEX));
        }

        canvas->setCursor(0, DISPLAY_HEIGHT - 24);
        uint8_t encoder_value = encoder.read();
        canvas->println("{L: " + String((*event.layer), DEC) + ", R: " + String(encoder_value, DEC) + " }");
    }

    
    canvas->setCursor(0, DISPLAY_HEIGHT - 24);
    canvas->setTextSize(3);
    canvas->println(event.methods.get_layer_name(*event.layer));

    canvas->drawBitmap(0, 0, ditto_bitmap[current_frame], 135, 135, 0xffff);

    if(neopixel_enabled) {
        gfx_set_led(0, event.methods.get_layer_color(*event.layer));
    } else {
        gfx_clear_leds();
    }
}

void task_user_animation_frame(event_t event) {
    current_frame += 1;
    if(current_frame >= DITTO_FRAMES) {
        current_frame = 0;
    }
}
