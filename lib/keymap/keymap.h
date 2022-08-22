
#pragma once

#include <Arduino.h>
#include <vector>
#include "matrix.h"

class Keymap 
{
    private:
        Matrix _matrix;
        int ActiveLayer;
        USBHIDConsumerControl consumer;
        // Keymap map;
        // WebServer server;
        // Preferences preferences;

    public:
        Keymap(Matrix, USBHIDConsumerControl);
        Keymap();
        void run();
        uint8_t getKeycode();
};
