
#pragma once

#include <Arduino.h>
#include <vector>

#include "USB.h"
#include "USBHIDConsumerControl.h"
#include "USBHIDKeyboard.h"

#include "keycodes.hpp"
#include "../../config/config.hpp"
#include "../graphics/graphics.hpp"

void usb_init();
void handle_user_tasks();
void handle_state(byte state, uint16_t size);
void handle_event(event_t event);
void flush();
void press(uint16_t keycode);
void release(uint16_t keycode);
void press_raw(uint8_t keycode);
void release_raw(uint8_t keycode);
void print(String str);
void println(String str);
