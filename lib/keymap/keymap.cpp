#include "keymap.h"

#include "matrix.h"

Keymap::Keymap(Matrix matrix) {
    this->_matrix = matrix;
}

void Keymap::run() {

}

uint8_t Keymap::getKeycode() {
    return 0;
}