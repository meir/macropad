#include "keymap.hpp"

#ifdef KEYMAP
std::vector<std::vector<uint16_t>> keymap = KEYMAP;
#else
std::vector<std::vector<uint16_t>> keymap = {};
#endif

#ifdef LAYER_NAMES
std::vector<String> layerNames = LAYER_NAMES;
#else
std::vector<String> layerNames = {};
#endif

#ifdef LAYER_COLORS
std::vector<uint32_t> layerColors = LAYER_COLORS;
#else
std::vector<uint32_t> layerColors = {};
#endif

#if defined(ENCODER_PIN_A) && defined(ENCODER_PIN_B)
Encoder encoder(ENCODER_PIN_A, ENCODER_PIN_B);
#endif

Keymap::Keymap(Matrix matrix, USBHIDConsumerControl _consumer, USBHIDKeyboard _keyboard) {
    this->_matrix = matrix;
    this->ActiveLayer = 0;
    this->consumer = _consumer;
    this->keyboard = _keyboard;
}

Keymap::Keymap() {}


void Keymap::run() {
    gfx_reset();
    _matrix.Scan();
    
    int encoderValue = encoder.read();

    #ifdef DEBUG
    gfx_println("Encoder: " + String(encoderValue, DEC));
    #endif

    #ifdef ROTARY_DIVIDER
    int rotaryDivider = ROTARY_DIVIDER;
    #else
    int rotaryDivider = 4;
    #endif

    this->ActiveLayer = (encoderValue / rotaryDivider) % keymap.size();
    led_setColor(this->currentLayerColor());
    gfx_println("Layer: " + this->currentLayerName());

    std::vector<uint16_t> layer = this->currentLayer();
    for(int i = 0; i < layer.size(); i++) {
        uint16_t state = this->_matrix.GetState(i);
        if(state > 0) {
            uint16_t key = layer.at(i);
            this->keyboard.pressRaw(key);
        }else{
            this->keyboard.releaseRaw(layer.at(i));
        }
    }
}

String Keymap::currentLayerName() {
    if(layerNames.size() > this->ActiveLayer) {
        return layerNames.at(this->ActiveLayer);
    }else{
        return String(this->ActiveLayer, DEC);
    }
}

std::vector<uint16_t> Keymap::currentLayer() {
    if(this->ActiveLayer >= 0 && this->ActiveLayer < keymap.size()) {
        return keymap.at(this->ActiveLayer);
    }
    this->ActiveLayer = 0;
    return keymap.at(0);
}

uint32_t Keymap::currentLayerColor() {
    if(layerColors.size() > this->ActiveLayer) {
        return layerColors.at(this->ActiveLayer);
    }else{
        return WHITE;
    }
}