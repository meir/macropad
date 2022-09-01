
#pragma once

#include <Arduino.h>
#include <vector>

class Matrix {
    private:
        std::vector<uint8_t> columns;
        std::vector<uint8_t> rows;

        uint32_t  states;

    public:
        Matrix(std::vector<uint8_t> columns, std::vector<uint8_t> rows);

        void scan();
        uint16_t size();
        bool state(uint16_t index);
        uint32_t  state();
};
