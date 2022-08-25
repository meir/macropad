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
        pinMode(_columns.at(i), OUTPUT);
    }

    for(int i = 0; i < _rows.size(); i++) {
        pinMode(_rows.at(i), INPUT);
    }

    for(int i = 0; i < _states.size(); i++) {
        _states.at(i) = 0;
    }
}

// A2 -> A0  |  A2 -> A1  |  A3 -> A0
// A4 -> A0  |        A4 -> A1

void Matrix::Scan() {
    for(int i = 0; i < _rows.size(); i++) {
        int row = _rows.at(i);
        pinMode(row, INPUT_PULLUP);

        for(int j = 0; j < _columns.size(); j++) {
            int column = _columns.at(j);
            digitalWrite(column, HIGH);
            int state = digitalRead(row);
            digitalWrite(column, LOW);

            if(state == HIGH) {
                _states.at(i * _columns.size() + j) += 1;
            } else {
                _states.at(i * _columns.size() + j) = 0;
            }
        }

        pinMode(row, INPUT);
    }

    // for(int x = 0; x < _rows.size(); x++) {
    //     int row = _rows.at(x);
    //     pinMode(row, INPUT_PULLUP);
        
    //     for(int y = 0; y < _columns.size(); y++) {
    //         int column = _columns.at(y);

    //         pinMode(column, OUTPUT);
    //         digitalWrite(column, LOW);

    //         int state = digitalRead(row);
    //         if(state == HIGH) {
    //             _states.at(x * _columns.size() + y) = 0;
    //             continue;
    //         }
            
    //         _states.at(x * _columns.size() + y) += 1;

    //         pinMode(column, INPUT);
    //     }
    //     pinMode(row, INPUT);
    // }

    // for(int x = 0; x < _columns.size(); x++) {
    //     int col = _columns.at(x);
    //     pinMode(col, OUTPUT);
    //     digitalWrite(col, LOW);

    //     for(int y = 0; y < _rows.size(); y++) {
    //         int row = _rows.at(y);
    //         pinMode(row, INPUT_PULLUP);
    //         int state = digitalRead(row);
            
    //         if(state == HIGH) {
    //             _states.at(y + (_columns.size() * x)) = 0;
    //             continue;
    //         }

    //         _states.at(y + (_columns.size() * x)) += 1;

    //         pinMode(row, INPUT);
    //     }

    //     pinMode(col, INPUT);
    // }
}

int Matrix::Length() {
    return _states.size();
}

int Matrix::GetState(int index) {
    return _states.at(index);
}