
#pragma once

#include "../matrix/matrix.hpp"
#include "../config/config.hpp"
#include "../handler/handler.hpp"

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

        std::vector<std::vector<uint32_t>> keymap;
        std::vector<String> layerNames;
        std::vector<uint32_t> layerColors;

        std::vector<int> last_scan;
        
        // Keymap map;
        // WebServer server;
        // Preferences preferences;

    public:
        Keymap(Matrix, USBHIDConsumerControl, USBHIDKeyboard);
        Keymap();
        void run();
        uint32_t getKeycode();
        String currentLayerName();
        uint32_t currentLayerColor();
        std::vector<uint32_t> currentLayer();
};