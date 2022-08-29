
#include "handler.hpp"

#include "../graphics/graphics.hpp"

#include <String>

void keycode_handler(event_t event) {
    switch(event.keycode) {
        // case KEY_MACRO_MIN...KEY_LAYER_TOGGLE_MAX:
        //     event.key_type = KT_MACRO;

        //     //TODO: To be implemented

            // break;
        case KC_NO...KC_EXSEL:

            if(event.type == KDN) {
                event.keyboard.pressRaw(event.keycode);
            }else{
                event.keyboard.releaseRaw(event.keycode);
            }

            break;
        case KC_LEFT_CTRL...KC_RIGHT_GUI:

            if(event.type == KDN) {
                event.keyboard.pressRaw(event.keycode);
            }else{
                event.keyboard.releaseRaw(event.keycode);
            }

            break;
        case KC_MEDIA_POWER...KC_MEDIA_PAN:

            uint16_t media_keycode = event.keycode ^ KEY_MEDIA_MIN;

            if(event.type == KDN) {
                event.consumer.press(media_keycode);
            }else{
                event.consumer.release();
            }

            break;
    }
}