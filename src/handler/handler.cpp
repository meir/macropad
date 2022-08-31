
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
                    case KEY_DOWN: event.keyboard.pressRaw(event.keycode); break;
                    case KEY_UP: event.keyboard.releaseRaw(event.keycode); break;
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
                    case KEY_DOWN: event.keyboard.pressRaw(event.keycode); break;
                    case KEY_UP: event.keyboard.releaseRaw(event.keycode); break;
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
