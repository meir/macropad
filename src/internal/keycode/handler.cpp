
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
byte previous_state = 0;
KeyReport report;

void usb_init() {
    usb_config_t config = usb_config();

    USB.manufacturerName(config.manufacturer_name.c_str());
    USB.productName(config.product_name.c_str());
    USB.serialNumber(config.serial_number.c_str());

    consumer.begin();
    keyboard.begin();
    USB.begin();
}

#ifdef DISPLAY_ANIMATION_ENABLED
uint64_t last_animation_frame = 0;
#endif

void handle_user_tasks() {
    event_t event;
    event.methods = methods;
    event.layer = &layer;
    event.layer_count = keymap({}).size();

    #ifdef ENCODER_ENABLED
    event.type = EVENT_ENCODER_TICK;
    task_user_encoder_tick(event);
    #endif

    #ifdef DISPLAY_ENABLED
    event.type = EVENT_DISPLAY_TICK;
    task_user_display_tick(event);
    #endif

    #ifdef DISPLAY_ANIMATION_ENABLED
    if (millis() - last_animation_frame >= 1000 / DISPLAY_ANIMATION_FPS) {
        last_animation_frame = millis();
        event.type = EVENT_ANIMATION_FRAME;
        task_user_animation_frame(event);
    }
    #endif
}

std::vector<keydata_t> keystates = {};
int8_t tap_layer = -1; // just hardcode taplayers for now since its much easier than having an event array for it

int16_t has_keystate(uint8_t key_id) {
    std::vector<keydata_t>::iterator i = keystates.begin();
    while(i != keystates.end()) {
        if (i->key_id == key_id) {
            return i - keystates.begin();
        }
        i++;
    }
    return -1;
}

void handle_state(byte state, uint16_t size) {
    if (state == previous_state) {
        return;
    }

    LAYER layer_map = get_layer_keys(layer);

    for(uint16_t i = 0; i < size; i++) {
        byte current = (state >> i) & 1;
        byte previous = (previous_state >> i) & 1;
        if (previous == current) continue;

        event_t event;
        event.methods = methods;
        event.layer = &layer;
        event.layer_count = keymap({}).size();
        event.type = event_type_t(current);

        int16_t state_id = has_keystate(i);

        if(state_id >= 0) {
            keydata_t keystate = keystates.at(state_id);
            event.keydata = keystate;
        }else{
            keycode_t key = layer_map[i];
            uint8_t type = (key >> 12);
            uint8_t keycode = key ^ (type << 8);

            keydata_t keydata = {
                key,
                keycode,
                (keycode_type_t)type,
                i,
                layer,
            };
            event.keydata = keydata;
        }

        handle_event(event);
        if (state_id >= 0) {
            // Not sure why it only works here and not inside the first (state_id >= 0) block
            keystates.erase(keystates.begin() + state_id);
        }
    }

    previous_state = state;
    flush();
}

void flush() {
    keyboard.sendReport(&report);
}

void handle_event(event_t event) {
    if(event.type == EVENT_KEY_DOWN) keystates.push_back(event.keydata);

    switch(event.keydata.type) {
        case T_DEFAULT:
            switch(event.type) {
                case EVENT_KEY_DOWN:
                    if(HAS_MOD(event.keydata.key)) press_raw(MOD(event.keydata.key));
                    press_raw(event.keydata.keycode);
                    break;
                case EVENT_KEY_UP:
                    release_raw(event.keydata.keycode);
                    if(HAS_MOD(event.keydata.key)) release_raw(MOD(event.keydata.key));
                    break;
            }
            break;

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
            switch(event.type) {
                case EVENT_KEY_DOWN:
                    (*event.layer) = event.keydata.keycode;
                    return; // prevent release event to be called
                case EVENT_KEY_UP:
                    (*event.layer) = event.keydata.layer;
                    return; // prevent release event to be called
            }
            break;

        case T_LAYER_TAP:
            switch(event.type) {
                case EVENT_KEY_DOWN:
                    (*event.layer) = event.keydata.keycode;
                    tap_layer = event.keydata.layer;
                case EVENT_KEY_UP:
                    return; // prevent release event to be called

                case EVENT_TAP_LAYER:
                    (*event.layer) = event.keydata.layer;
                    break;
            }
            break;

        case T_LAYER_TOGL:
            switch(event.type) {
                case EVENT_KEY_DOWN:
                    (*event.layer) = event.keydata.keycode;
                    return; // prevent release event to be called
            }
            break;
        
        case T_CUSTOM:
            task_user_keycode_custom(event);
            break;
    }

    switch(event.type) {
        case EVENT_KEY_DOWN:
            onpress(event);
            break;
        case EVENT_KEY_UP:
            onrelease(event);
            break;
    }
}

void onpress(event_t e) {
    task_user_onpress(e);
}

void onrelease(event_t e) {
    if(tap_layer >= 0) {
        (*e.layer) = tap_layer;
        tap_layer = -1;
    }

    task_user_onrelease(e);
}

void press(uint16_t keycode) {
    uint8_t type = keycode >> 8;
    uint8_t code = keycode;

    keydata_t keydata = {code, keycode_type_t(type)};
    event_t event = {EVENT_KEY_DOWN, keydata, &layer, uint8_t(keymap({}).size()), methods};

    handle_event(event);
}

void release(uint16_t keycode) {
    uint8_t type = keycode >> 8;
    uint8_t code = keycode;

    keydata_t keydata = {code, keycode_type_t(type)};
    event_t event = {EVENT_KEY_UP, keydata, &layer, uint8_t(keymap({}).size()), methods};

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