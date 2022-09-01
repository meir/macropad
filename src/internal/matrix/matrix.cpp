
#include "matrix.hpp"

Matrix::Matrix(std::vector<uint8_t> columns, std::vector<uint8_t> rows) {
    this->columns = columns;
    this->rows = rows;
    this->states = 0b0 << this->size();
}

void Matrix::scan() {
    for(uint8_t r = 0; r < this->rows.size(); r++) {
        uint8_t row = this->rows.at(r);
        pinMode(row, INPUT_PULLUP);

        for(uint8_t c = 0; c < this->columns.size(); c++) {
            uint8_t column = this->columns.at(c);

            pinMode(column, OUTPUT);
            int state = digitalRead(row);
            pinMode(column, INPUT);

            uint16_t pos = (r * this->columns.size() + c);
            states = states ^ ((!state << pos) ^ states) & (0b1 << pos);
        }

        pinMode(row, INPUT);
    }
}

uint16_t Matrix::size() {
    return this->columns.size() * this->rows.size();
}

bool Matrix::state(uint16_t index) {
    return (states >> index) & 0b1;
}

uint32_t  Matrix::state() {
    return states;
}