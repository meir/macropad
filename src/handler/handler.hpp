
#pragma once

#include <Arduino.h>
#include <Encoder.h>
#include "../keycodes/keycodes.hpp"

#include "USB.h"
#include "USBHIDConsumerControl.h"
#include "USBHIDKeyboard.h"

#include <vector>

enum event_type_t {
    REST = 0,
    KEY_UP,
    KEY_DOWN,
    ENCODER_TICK,
    DISPLAY_TICK,
};

struct event_t {
    event_type_t type;
    uint32_t keycode;

    bool resolved;

    USBHIDConsumerControl consumer;
    USBHIDKeyboard keyboard;
    uint16_t* layer;
    uint16_t layers;

    String layername;
    uint32_t layercolor;
};

typedef bool (*key_checker_t)(event_t *event);
typedef void (*key_handler_t)(event_t event);

typedef struct {
    key_checker_t key_checker;
    key_handler_t key_handler;
} keycode_callbacks_t;

extern keycode_callbacks_t keycode_callbacks[];

void keycode_handler(event_t event);

void task_user_keycode(event_t event) __attribute__ ((weak));
void task_user_encoder_tick(event_t event) __attribute__ ((weak));
void task_user_display_tick(event_t event) __attribute__ ((weak));