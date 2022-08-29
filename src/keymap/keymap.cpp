#include "keymap.hpp"

#if defined(ENCODER_PIN_A) && defined(ENCODER_PIN_B)
Encoder encoder(ENCODER_PIN_A, ENCODER_PIN_B);
#endif

Keymap::Keymap(Matrix matrix, USBHIDConsumerControl _consumer, USBHIDKeyboard _keyboard) {
    this->_matrix = matrix;
    this->ActiveLayer = 0;
    this->consumer = _consumer;
    this->keyboard = _keyboard;

    #ifdef KEYMAP
    this->keymap = KEYMAP;
    #else
    this->keymap = {};
    #endif

    #ifdef LAYER_NAMES
    this->layerNames = LAYER_NAMES;
    #else
    this->layerNames = {};
    #endif

    #ifdef LAYER_COLORS
    this->layerColors = LAYER_COLORS;
    #else
    this->layerColors = {};
    #endif

    this->_matrix.Scan();
    this->last_scan = this->_matrix.GetStates();
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
    gfx_println("Layer: \n" + this->currentLayerName());

    std::vector<uint32_t> layer = this->currentLayer();
    for(int i = 0; i < layer.size(); i++) {
        uint32_t state = this->_matrix.GetState(i);
        event_type_t event = KUP;
        if(last_scan.at(i) != state) {
            if(state == 1) {
                event = KDN;
            }
        }

        // keycode_handler(layer.at(i), event, this->consumer, this->keyboard);
        keycode_handler({
            .type = event,
            .keycode = layer.at(i),

            .consumer = this->consumer,
            .keyboard = this->keyboard
        });
    }

    this->last_scan = _matrix.GetStates();
}

String Keymap::currentLayerName() {
    if(layerNames.size() > this->ActiveLayer) {
        return layerNames.at(this->ActiveLayer);
    }else{
        return String(this->ActiveLayer, DEC);
    }
}

std::vector<uint32_t> Keymap::currentLayer() {
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