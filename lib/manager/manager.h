
#pragma once

#include "matrix.h"
#include "keymap.h"

#include <WString.h>
#include <vector>

class Manager 
{
    private:
        Matrix _matrix;
        Keymap _map;
        // WebServer server;
        // Preferences preferences;

    public:
        Manager();
        void run();
};
