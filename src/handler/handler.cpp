
#include "handler.hpp"

#include "../graphics/graphics.hpp"

#include <String>

std::vector<layer_event_t> layer_events;

void keycode_handler(event_t event) {
    for(uint32_t i = 0; i < layer_events.size(); i++) {
        layer_event_t layer_event = layer_events.at(i);

        switch(layer_event.type) {
            case LAYER_HLD:
                if(layer_event.key_id == event.id) {
                    if(event.type != KEY_UP) return;
                    (*event.layer) = layer_event.layer;
                    layer_events.erase(layer_events.begin() + i);
                }
                goto doneEvent;
            case LAYER_OTK:
                if(event.type == KEY_DOWN) {
                    (*event.layer) = layer_event.layer;
                    layer_events.erase(layer_events.begin() + i);
                }
                goto doneEvent;
        }
    }

    doneEvent:

    switch(event.keycode) {
        case SWITCH_DEFAULT:
            {
                event.keycode = FROM_DEFAULT(event.keycode);
                task_user_keycode(event);
                if(event.resolved) break;

                switch(event.type) {
                    case KEY_DOWN: press(event); break;
                    case KEY_UP: release(event); break;
                }
                break;
            }
        case SWITCH_MACRO:
            {
                event.keycode = FROM_MACRO(event.keycode);
                task_user_keycode(event);
                if(event.resolved) break;

                break;
            }
        case SWITCH_FUNCTION:
            {
                event.keycode = FROM_FUNCTION(event.keycode);
                task_user_keycode(event);
                if(event.resolved) break;

                switch(event.type) {
                    case KEY_DOWN: press(event); break;
                    case KEY_UP: release(event); break;
                }

                break;
            }
        case SWITCH_MEDIA:
            {
                event.keycode = FROM_MEDIA(event.keycode);
                task_user_keycode(event);
                if(event.resolved) break;

                switch(event.type) {
                    case KEY_DOWN: event.consumer.press(event.keycode); break;
                    case KEY_UP: event.consumer.release(); break;
                }

                break;
            }
        case SWITCH_RGB:
            {
                event.keycode = FROM_RGB(event.keycode);
                task_user_keycode(event);
                if(event.resolved) break;

                break;
            }
        case SWITCH_MOUSE:
            {
                event.keycode = FROM_MOUSE(event.keycode);
                task_user_keycode(event);
                if(event.resolved) break;

                break;
            }
        case SWITCH_LAYER_HOLD:
            {
                event.keycode = FROM_LAYER_HOLD(event.keycode);
                task_user_keycode(event);
                if(event.resolved) break;

                if(event.type != KEY_DOWN) break;

                layer_event_t layer_event = {
                    .type = LAYER_HLD,
                    .layer = (*event.layer),
                    .key_id = event.id,
                };

                layer_events.push_back(layer_event);
                (*event.layer) = event.keycode;
                break;
            }
        case SWITCH_LAYER_TAP:
            {
                event.keycode = FROM_LAYER_TAP(event.keycode);
                task_user_keycode(event);
                if(event.resolved) break;

                if(event.type != KEY_DOWN) break;

                layer_event_t layer_event = {
                    .type = LAYER_OTK,
                    .layer = (*event.layer),
                    .key_id = event.id,
                };

                layer_events.push_back(layer_event);
                (*event.layer) = event.keycode;
                break;
            }
        case SWITCH_LAYER_TOGGLE:
            {
                event.keycode = FROM_LAYER_TOGGLE(event.keycode);
                task_user_keycode(event);
                if(event.resolved) break;

                if(event.type == KEY_DOWN) {
                    (*event.layer) = event.keycode;
                }
                break;
            }

        default:
            {
                task_user_keycode(event);
                if(event.resolved) break;
            }
    }
}

void press(uint32_t key) {
    event_t event;
    event.type = KEY_DOWN;
    event.keycode = key;
    press(event);
}

void press(event_t event) {
    uint8_t i;
    uint32_t k = event.keycode;
    if (k >= 0xE0 && k < 0xE8) {
        // it's a modifier key
        (*event.report).modifiers |= (1<<(k-0x80));
    } else if (k && k < 0xA5) {
        // Add k to the key report only if it's not already present
        // and if there is an empty slot.
        if ((*event.report).keys[0] != k && (*event.report).keys[1] != k && 
            (*event.report).keys[2] != k && (*event.report).keys[3] != k &&
            (*event.report).keys[4] != k && (*event.report).keys[5] != k) {
            
            for (i=0; i<6; i++) {
                if ((*event.report).keys[i] == 0x00) {
                    (*event.report).keys[i] = k;
                    break;
                }
            }
            if (i == 6) {
                return;
            }   
        }
    } else {
        //not a modifier and not a key
        return;
    }
}

void release(uint32_t key) {
    event_t event;
    event.type = KEY_DOWN;
    event.keycode = key;
    release(event);
}

void release(event_t event) {
    uint8_t i;
    uint32_t k = event.keycode;
    if (k >= 0xE0 && k < 0xE8) {
        // it's a modifier key
        (*event.report).modifiers &= ~(1<<(k-0x80));
    } else if (k && k < 0xA5) {
        // Test the key report to see if k is present.  Clear it if it exists.
        // Check all positions in case the key is present more than once (which it shouldn't be)
        for (i=0; i<6; i++) {
            if (0 != k && (*event.report).keys[i] == k) {
                (*event.report).keys[i] = 0x00;
            }
        }
    } else {
        //not a modifier and not a key
        return;
    }
}