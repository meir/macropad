
#include "manager.h"

#include "config.h"
#include "matrix.h"

#if defined(MATRIX_COLUMNS) && defined(MATRIX_ROWS)

std::vector<int> columns = MATRIX_COLUMNS;
std::vector<int> rows = MATRIX_ROWS;

USBHIDConsumerControl ConsumerControl;

Manager::Manager() {
    this->_matrix = *(new Matrix(columns, rows));
    this->_map = *(new Keymap(this->_matrix, ConsumerControl));
    _matrix.Init();
    ConsumerControl.begin();
    USB.begin();
}

void Manager::run() {
    _matrix.Scan();
    _map.run();
}

#endif