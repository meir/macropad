
#pragma once

#include <Arduino.h>
#include "../keycodes/keycodes.hpp"

typedef enum event_type_t {
    RST = 0,
    KUP = 1,
    KDN = 2,
    KTM = 3,
};

typedef struct event_t {
    uint16_t type: 5;
    uint16_t keycode: 3;
};

typedef bool (*key_checker_t)(event_t *event);
typedef void (*key_handler_t)(event_t event);

typedef struct {
    key_checker_t key_checker;
    key_handler_t key_handler;
} keycode_callbacks_t;

extern keycode_callbacks_t keycode_callbacks[];

void keycode_handler(uint16_t keycode);
