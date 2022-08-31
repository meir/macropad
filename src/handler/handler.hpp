
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
    VIRTUAL_LAYER_SWITCH,
};

struct event_t {
    event_type_t type;
    uint32_t id;
    uint32_t keycode;

    bool resolved;

    USBHIDConsumerControl consumer;
    USBHIDKeyboard keyboard;
    int16_t* layer;
    uint16_t layers;
    uint16_t virtual_layer;

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

enum layer_event_type_t {
    LAYER_HLD = 0,
    LAYER_OTK,
    LAYER_TOG,
};

struct layer_event_t {
    layer_event_type_t type;
    int16_t layer;
    uint32_t key_id;
};

void keycode_handler(event_t event);

typedef std::vector<std::vector<uint32_t>> KEYMAP;
KEYMAP keymap(KEYMAP pref) __attribute__ ((weak));

typedef std::vector<String> LAYER_NAMES;
LAYER_NAMES layer_names(LAYER_NAMES pref) __attribute__ ((weak));

typedef std::vector<uint32_t> LAYER_COLORS;
LAYER_COLORS layer_colors(LAYER_COLORS pref) __attribute__ ((weak));

void task_user_keycode(event_t event) __attribute__ ((weak));
void task_user_encoder_tick(event_t event) __attribute__ ((weak));
void task_user_display_tick(event_t event) __attribute__ ((weak));