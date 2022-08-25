#include "keymap.hpp"

#ifdef KEYMAP
std::vector<std::vector<uint16_t>> keymap = KEYMAP;
#else
std::vector<std::vector<uint16_t>> keymap = {};
#endif

Keymap::Keymap(Matrix matrix, USBHIDConsumerControl _consumer, USBHIDKeyboard _keyboard) {
    this->_matrix = matrix;
    this->ActiveLayer = 0;
    this->consumer = _consumer;
    this->keyboard = _keyboard;

    gfx_init();
}

Keymap::Keymap() {}


void Keymap::run() {
    gfx_reset();
    _matrix.Scan();
    std::vector<uint16_t> layer = this->currentLayer();
    for(int i = 0; i < layer.size(); i++) {
        uint16_t state = this->_matrix.GetState(i);
        gfx_println(String(state, DEC));
        if(state > 0) {
            uint16_t key = layer.at(i);
            this->keyboard.pressRaw(key);
        }else{
            this->keyboard.releaseRaw(layer.at(i));
        }
    }
}

std::vector<uint16_t> Keymap::currentLayer() {
    if(this->ActiveLayer >= 0 && this->ActiveLayer < keymap.size()) {
        return keymap.at(this->ActiveLayer);
    }
    this->ActiveLayer = 0;
    return keymap.at(0);
}