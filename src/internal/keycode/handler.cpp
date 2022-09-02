
#include "handler.hpp"
#include "../../config/config.hpp"

USBHIDConsumerControl consumer;
USBHIDKeyboard keyboard;

methods_t methods = {
    press,
    release,
    press_raw,
    release_raw,
    print,
    println,
    flush,
    get_layer_keys,
    get_layer_name,
    get_layer_color,
};

uint8_t layer = 0;
uint8_t layer_count = keymap({}).size();

byte previous_state = 0;

KeyReport report;

void usb_init() {
    consumer.begin();
    keyboard.begin();
    USB.begin();
}

void handle_user_tasks() {
    event_t event;
    event.methods = methods;
    event.layer = &layer;
    event.layer_count = layer_count;

    #ifdef ENCODER_ENABLED
    event.type = EVENT_ENCODER_TICK;
    task_user_encoder_tick(event);
    #endif

    #ifdef DISPLAY_ENABLED
    event.type = EVENT_DISPLAY_TICK;
    task_user_display_tick(event);
    #endif
}

void handle_state(byte state, uint16_t size) {
    handle_user_tasks();

    if (state == previous_state) {
        return;
    }

    LAYER layer_map = get_layer_keys(layer);

    for(uint16_t i = 0; i < size; i++) {
        byte previous = (previous_state >> i) & 1;
        byte current = (state >> i) & 1;

        if (previous == current) continue;

        keycode_t key = layer_map[i];
        uint8_t type = key >> 8;
        uint8_t keycode = key ^ (type << 8);

        keydata_t keydata = {
            keycode,
            key,
            (keycode_type_t)type,
        };

        event_t event = {
            .type = event_type_t(current),
            .keydata = keydata,
            .layer = &layer,
            .layer_count = layer_count,
            .methods = methods,
        };

        handle_event(event);
    }

    previous_state = state;
    flush();
}

void flush() {
    keyboard.sendReport(&report);
}

void handle_event(event_t event) {
    // if(task_user_keycode(event)) return;

    switch(event.keydata.type) {
        case T_DEFAULT:
            switch(event.type) {
                case EVENT_KEY_DOWN:
                    if(HAS_MOD(event.keydata.key)) {
                        uint8_t mod = MOD(event.keydata.key);
                        press_raw(mod);
                    }

                    press_raw(event.keydata.keycode);
                    break;
                case EVENT_KEY_UP:
                    release_raw(event.keydata.keycode);

                    if(HAS_MOD(event.keydata.key)) {
                        uint8_t mod = MOD(event.keydata.key);
                        release_raw(mod);
                    }
                    break;
            }
        case T_MOD:
            switch(event.type) {
                case EVENT_KEY_DOWN:
                    press_raw(event.keydata.keycode);
                    break;
                case EVENT_KEY_UP:
                    release_raw(event.keydata.keycode);
                    break;
            }
            break;
        case T_MEDIA:
            switch(event.type) {
                case EVENT_KEY_DOWN:
                    consumer.press(event.keydata.keycode);
                    break;
                case EVENT_KEY_UP:
                    consumer.release();
                    break;
            }
            break;
        case T_LAYER_HOLD:
            // if(!task_user_keycode_layer_hold(event)) break;
        case T_LAYER_SWAP:
            // if(!task_user_keycode_layer_swap(event)) break;
        case T_LAYER_TOGL:
            // if(!task_user_keycode_layer_toggle(event)) break;
        
        case T_CUSTOM:
            task_user_keycode_custom(event);
            break;
    }
}

void press(uint16_t keycode) {
    uint8_t type = keycode >> 8;
    uint8_t code = keycode;

    keydata_t keydata = {code, keycode_type_t(type)};
    event_t event = {EVENT_KEY_DOWN, keydata, &layer, layer_count, methods};

    handle_event(event);
}

void release(uint16_t keycode) {
    uint8_t type = keycode >> 8;
    uint8_t code = keycode;

    keydata_t keydata = {code, keycode_type_t(type)};
    event_t event = {EVENT_KEY_UP, keydata, &layer, layer_count, methods};

    handle_event(event);
}

void press_raw(uint8_t keycode) {
    if (keycode >= 0xE0 && keycode < 0xE8) {
        report.modifiers |= (1 << (keycode - 0x80));
    } else if (keycode && keycode < 0xA5) {
        if (report.keys[0] != keycode && report.keys[1] != keycode && 
            report.keys[2] != keycode && report.keys[3] != keycode &&
            report.keys[4] != keycode && report.keys[5] != keycode) {
            
            for (uint8_t i = 0; i < 6; i++) {
                if (report.keys[i] == 0x00) {
                    report.keys[i] = keycode;
                    break;
                }
            }
        }
    }
} 

void release_raw(uint8_t keycode) {
    if (keycode >= 0xE0 && keycode < 0xE8) {
        report.modifiers &= ~(1 << (keycode - 0x80));
    } else if (keycode && keycode < 0xA5) {
        for (uint8_t i = 0; i < 6; i++) {
            if (0 != keycode && report.keys[i] == keycode) {
                report.keys[i] = 0x00;
            }
        }
    }
}

void print(String str) {
    keyboard.print(str);
}

void println(String str) {
    keyboard.println(str);
}

LAYER get_layer_keys(uint8_t layer) {
    KEYMAP map = keymap({});
    if(layer >= map.size()) layer = 0;
    return map[layer];
}

String get_layer_name(uint8_t layer) {
    LAYER_NAMES names = layer_names({});
    if(layer >= names.size()) layer = 0;
    return names[layer];
}

uint32_t get_layer_color(uint8_t layer) {
    LAYER_COLORS colors = layer_colors({});
    if(layer >= colors.size()) layer = 0;
    return colors[layer];
}