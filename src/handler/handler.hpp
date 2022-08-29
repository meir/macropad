
#pragma once

#include <Arduino.h>
#include "../keycodes/keycodes.hpp"

#include "USB.h"
#include "USBHIDConsumerControl.h"
#include "USBHIDKeyboard.h"

typedef enum event_type_t {
    RST = 0,
    KUP = 1,
    KDN = 2,
    KTM = 3,
};

typedef struct event_t {
    event_type_t type;
    uint32_t keycode;

    USBHIDConsumerControl consumer;
    USBHIDKeyboard keyboard;
};

typedef bool (*key_checker_t)(event_t *event);
typedef void (*key_handler_t)(event_t event);

typedef struct {
    key_checker_t key_checker;
    key_handler_t key_handler;
} keycode_callbacks_t;

extern keycode_callbacks_t keycode_callbacks[];

void keycode_handler(event_t event);
