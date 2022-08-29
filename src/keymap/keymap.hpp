
#pragma once

#include "../matrix/matrix.hpp"
#include "../config/config.hpp"
#include "../handler/handler.hpp"

#include "../graphics/graphics.hpp"

#include "USB.h"
#include "USBHIDConsumerControl.h"
#include "USBHIDKeyboard.h"

#include <Arduino.h>
#include <vector>

class Keymap 
{
    private:
        Matrix _matrix;
        uint16_t ActiveLayer;
        USBHIDConsumerControl consumer;
        USBHIDKeyboard keyboard;

        std::vector<std::vector<uint32_t>> keymap;
        std::vector<String> layerNames;
        std::vector<uint32_t> layerColors;

        byte last_scan;
        
        // Keymap map;
        // WebServer server;
        // Preferences preferences;

    public:
        Keymap(Matrix matrix, USBHIDConsumerControl consumer, USBHIDKeyboard keyboard);
        Keymap();
        void run();
        void setLayer(uint32_t layer);
        std::vector<std::vector<uint32_t>> getLayers();
        String currentLayerName();
        uint32_t currentLayerColor();
        std::vector<uint32_t> currentLayer();
        void user_tasks();
};