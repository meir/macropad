#include "keymap.h"
#include "config.h"
#include "matrix.h"
#include <vector>
#include "USB.h"
#include "USBHIDConsumerControl.h"
#include <Arduino.h>

Keymap::Keymap(Matrix matrix, USBHIDConsumerControl _consumer) {
    this->_matrix = matrix;
    this->ActiveLayer = 0;
    this->consumer = _consumer;
}

void Keymap::run() {
    std::vector<int> layer = this.CurrentLayer();
    for(int i = 0; i < layer.size(); i++) {
        int state = this->_matrix.GetState(i);
        if(state > 0) {
            int key = layer.get(i);

        }
    }
}

std::vector<int> Keymap::CurrentLayer() {
    if(this->ActiveLayer >= 0 && this->ActiveLayer < KEYMAP.size()) {
        return KEYMAP.get(this->ActiveLayer);
    }
    this->ActiveLayer = 0;
    return KEYMAP.get(0);
}