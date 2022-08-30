#include "matrix.hpp"

Matrix::Matrix(std::vector<int> columns, std::vector<int> rows) {
    _columns = columns;
    _rows = rows;

    _states = 0b0 << (columns.size() * rows.size());
}

Matrix::Matrix() {}

void Matrix::Init() {
    for(int i = 0; i < _columns.size(); i++) {
        pinMode(_columns.at(i), INPUT);
    }

    for(int i = 0; i < _rows.size(); i++) {
        pinMode(_rows.at(i), INPUT_PULLUP);
    }

    _states = 0b0 << _rows.size() * _columns.size();
}

void Matrix::Scan() {
    for(int r = 0; r < _rows.size(); r++) {
        int row = _rows.at(r);
        pinMode(row, INPUT_PULLUP);

        for(int c = 0; c < _columns.size(); c++) {
            int column = _columns.at(c);

            pinMode(column, OUTPUT);
            int state = digitalRead(row);
            pinMode(column, INPUT);

            #ifdef DEBUG
            gfx_println("(" + String(c, DEC) + ", " + String(r, DEC) + ")[" + String(r * _columns.size() + c, DEC) + "] = " + String(!state, DEC));
            #endif

            int pos = (r * _columns.size() + c);
            _states = _states ^ ((!state << pos) ^ _states) & (0b1 << pos);
        }

        pinMode(row, INPUT);
    }
}

int Matrix::Length() {
    return _rows.size() * _columns.size();
}

bool Matrix::GetState(int index) {
    return (_states & 0b1 << index) > 0;
}

byte Matrix::GetStates() {
    return _states;
}