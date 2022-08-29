
#pragma once

#include <Arduino.h>
#include <vector>

#include "../graphics/graphics.hpp"
#include "../config/config.hpp"

class Matrix
{
    private:
        std::vector<int> _columns;
        std::vector<int> _rows;

        byte _states;

    public:
        Matrix(std::vector<int> columns, std::vector<int> rows);
        Matrix();
        void Init();
        void Scan();
        int Length();
        bool GetState(int index);
        byte GetStates();
};
