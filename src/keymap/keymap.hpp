
#pragma once

#include "../matrix/matrix.hpp"
#include "../config/config.hpp"

#include "../graphics/graphics.hpp"

#include "USB.h"
#include "USBHIDConsumerControl.h"
#include "USBHIDKeyboard.h"

#include <Encoder.h>
#include <Arduino.h>
#include <vector>

class Keymap 
{
    private:
        Matrix _matrix;
        int ActiveLayer;
        USBHIDConsumerControl consumer;
        USBHIDKeyboard keyboard;
        // Keymap map;
        // WebServer server;
        // Preferences preferences;

    public:
        Keymap(Matrix, USBHIDConsumerControl, USBHIDKeyboard);
        Keymap();
        void run();
        uint16_t getKeycode();
        String currentLayerName();
        uint32_t currentLayerColor();
        std::vector<uint16_t> currentLayer();
};