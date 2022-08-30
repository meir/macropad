
#include "handler.hpp"

#include "../graphics/graphics.hpp"

#include <String>

void keycode_handler(event_t event) {

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
        case SWITCH_LAYER:
            {
                break;
            }

        default:
            {
                task_user_keycode(event);
                if(event.resolved) break;
            }
    }
}
