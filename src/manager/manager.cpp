
#include "manager.hpp"

std::vector<int> columns = MATRIX_COLUMNS;
std::vector<int> rows = MATRIX_ROWS;

USBHIDConsumerControl ConsumerControl;
USBHIDKeyboard Keyboard;

Manager::Manager() {
    this->_matrix = *(new Matrix(columns, rows));
    this->_map = *(new Keymap(this->_matrix, ConsumerControl, Keyboard));
    _matrix.Init();

    preinit_usb();

    ConsumerControl.begin();
    Keyboard.begin();
    USB.begin();
}

void Manager::run() {
    _map.run();
}