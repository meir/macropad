
#pragma once

#include "../matrix/matrix.hpp"
#include "../keymap/keymap.hpp"
#include "../config/config.hpp"

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
