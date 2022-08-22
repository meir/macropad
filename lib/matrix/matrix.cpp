#include "matrix.h"

#include <Arduino.h>
#include <vector>

Matrix::Matrix(std::vector<int> columns, std::vector<int> rows) : Matrix({}, {}) {
    _columns = columns;
    _rows = rows;

    for(int i = 0; i < _rows.size() * columns.size(); i++) {
      _states.push_back(0);
    }
}

Matrix::Matrix() {}

void Matrix::Init() {
    for(int i = 0; i < _columns.size(); i++) {
        pinMode(_columns.at(i), OUTPUT);
    }

    for(int i = 0; i < _rows.size(); i++) {
        pinMode(_rows.at(i), INPUT);
    }

    for(int i = 0; i < _states.size(); i++) {
        _states.at(i) = 0;
    }
}

void Matrix::Scan() {
    for(int x = 0; x < _columns.size(); x++) {
        int col = _columns.at(x);
        pinMode(col, OUTPUT);
        digitalWrite(col, LOW);

        for(int y = 0; y < _rows.size(); y++) {
            int row = _rows.at(y);
            pinMode(row, INPUT_PULLUP);
            int state = digitalRead(row);
            pinMode(row, INPUT);
            
            if(state == HIGH) {
                _states.at(y + (_columns.size() * x)) = 0;
                continue;
            }

            _states.at(y + (_columns.size() * x)) += 1;
        }

        pinMode(col, INPUT);
    }
}

int Matrix::Length() {
    return _states.size();
}

int Matrix::GetState(int index) {
    return _states.at(index);
}