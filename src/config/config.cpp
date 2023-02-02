
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

usb_config_t usb_config() {
    return {
        .product_name = "Avant-Garde",
        .manufacturer_name = "Flamingo.dev",
        .serial_number = "0",
    };
}

KEYMAP keymap(KEYMAP pref) {
    if(pref.size() != 0) return pref;
    return {
        {
            KC_PREV_TRACK, KC_PLAY_PAUSE, KC_NEXT_TRACK, 
            ____, LCTRL(KC_Z), LCTRL(KC_Y)
        },
        {
            KC_F13, KC_F14, KC_F15, 
            KC_F16, KC_F17, KC_F18
        },
        {
            KC_F19, KC_F20, KC_F21, 
            KC_F22, KC_F23, KC_F24
        },
        {
            LCTRL(KC_F13), LCTRL(KC_F14), LCTRL(KC_F15),
            LCTRL(KC_F16), LCTRL(KC_F17), LCTRL(KC_F18),
        },
        {
            LCTRL(KC_F19), LCTRL(KC_F20), LCTRL(KC_F21),
            LCTRL(KC_F22), LCTRL(KC_F23), LCTRL(KC_F24),
        },
        {
            KC_Q, KC_W, KC_E,
            KC_B, KC_R, KC_LCTRL,
        },
        {
            KC_TOGGLE_NEOPIXEL, KC_TOGGLE_LAYER_INFO, KC_TOGGLE_BACKLIGHT,
            ____, TAP(1), HOLD(2)
        }
    };
}

LAYER_NAMES layer_names(LAYER_NAMES pref) {
    if(pref.size() != 0) return pref;
    return {
        "Media",
        "F13-F18", 
        "F19-F24",
        "CTL F13-F18",
        "CTL F19-F24", 
        "League",
        "Toggles"
    };
}

LAYER_COLORS layer_colors(LAYER_COLORS pref) {
    if(pref.size() != 0) return pref;
    return {
        0xebeb54,
        0x7e2bcc, 
        0x7e2bcc, 
        0xd9276b, 
        0xd9276b,  
        0x2b7ecc,
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
    int8_t encoder_value = encoder.read();
    if (encoder_value < 0) {
        encoder_value = (event.layer_count * 10) - encoder_value;
    }
    int8_t layer_change = (encoder_value / ROTARY_DIVIDER) % event.layer_count;
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
    if(current_frame >= FRAMES) {
        current_frame = 0;
    }
}
