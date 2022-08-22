
#pragma once

#include <Arduino.h>
#include <vector>
#include "matrix.h"

class Keymap 
{
    private:
        Matrix _matrix;
        // Keymap map;
        // WebServer server;
        // Preferences preferences;

    public:
        Keymap(Matrix);
        Keymap();
        void run();
        uint8_t getKeycode();
};
