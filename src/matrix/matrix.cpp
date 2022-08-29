#include "matrix.hpp"

Matrix::Matrix(std::vector<int> columns, std::vector<int> rows) {
    _columns = columns;
    _rows = rows;

    for(int i = 0; i < _rows.size() * columns.size(); i++) {
      _states.push_back(0);
    }
}

Matrix::Matrix() {}

void Matrix::Init() {
    for(int i = 0; i < _columns.size(); i++) {
        pinMode(_columns.at(i), INPUT);
    }

    for(int i = 0; i < _rows.size(); i++) {
        pinMode(_rows.at(i), INPUT_PULLUP);
    }

    for(int i = 0; i < _states.size(); i++) {
        _states.at(i) = 0;
    }
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
            _states.at(r * _columns.size() + c) = !state;
        }

        pinMode(row, INPUT);
    }
}

int Matrix::Length() {
    return _states.size();
}

int Matrix::GetState(int index) {
    return _states.at(index);
}

std::vector<int> Matrix::GetStates() {
    return _states;
}