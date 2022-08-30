#include "keymap.hpp"

Keymap::Keymap(Matrix matrix, USBHIDConsumerControl _consumer, USBHIDKeyboard _keyboard) {
    this->_matrix = matrix;
    this->ActiveLayer = 0;
    this->consumer = _consumer;
    this->keyboard = _keyboard;

    this->_matrix.Scan();
    this->last_scan = this->_matrix.GetStates();
}

Keymap::Keymap() {}


void Keymap::run() {
    gfx_reset();
    _matrix.Scan();

    #ifdef DEBUG
    gfx_println("Encoder: " + String(encoderValue, DEC));
    #endif

    user_tasks();

    std::vector<uint32_t> layer = this->currentLayer();
    for(int i = 0; i < layer.size(); i++) {
        uint32_t state = this->_matrix.GetState(i);
        event_type_t event = REST;

        if(((last_scan & 0b1 << i) > 0) != state) {
            event = event_type_t(state + 1);
        }

        keycode_handler({
            .type = event,
            .keycode = layer.at(i),

            .resolved = false,

            .consumer = this->consumer,
            .keyboard = this->keyboard,

            .layer = &this->ActiveLayer,
            .layers = uint16_t(keymap({}).size()),

            .layername = this->currentLayerName(),
            .layercolor = this->currentLayerColor(),
        });
    }

    this->last_scan = _matrix.GetStates();
}

void Keymap::setLayer(uint32_t layer) {
    this->ActiveLayer = layer;
}

std::vector<std::vector<uint32_t>> Keymap::getLayers() {
    return keymap({});
}

String Keymap::currentLayerName() {
    if(layer_names({}).size() > this->ActiveLayer) {
        return layer_names({}).at(this->ActiveLayer);
    }else{
        return String(this->ActiveLayer, DEC);
    }
}

std::vector<uint32_t> Keymap::currentLayer() {
    if(this->ActiveLayer >= 0 && this->ActiveLayer < keymap({}).size()) {
        return keymap({}).at(this->ActiveLayer);
    }
    this->ActiveLayer = 0;
    return keymap({}).at(0);
}

uint32_t Keymap::currentLayerColor() {
    if(layer_colors({}).size() > this->ActiveLayer) {
        return layer_colors({}).at(this->ActiveLayer);
    }else{
        return WHITE;
    }
}

void Keymap::user_tasks() {
    uint16_t size = keymap({}).size();

    event_t ev = {
        .type = REST,
        .keycode = 0,

        .resolved = false,

        .consumer = this->consumer,
        .keyboard = this->keyboard,
        .layer = &this->ActiveLayer,
        .layers = size,
        .layername = this->currentLayerName(),
        .layercolor = this->currentLayerColor(),
    };

    #ifdef ENCODER_ENABLE
        ev.type = ENCODER_TICK;
        task_user_encoder_tick(ev);
    #endif

    #ifdef DISPLAY_ENABLE
        ev.type = DISPLAY_TICK;
        task_user_display_tick(ev);
    #endif
}