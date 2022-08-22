
#pragma once

#include <Arduino.h>

typedef enum event_type_t {
    RST = 0,
    KUP = 1,
    KDN = 2,
    KTM = 3,
};

typedef struct event_t {
    uint8_t type: 5;
    uint8_t keycode: 3;
};

typedef struct {
    key_checker_t key_checker;
    key_handler_t key_handler;
} keycode_callbacks_t;

extern keycode_callbacks_t keycode_callbacks[];
