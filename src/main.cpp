
#include <Arduino.h>
#include <vector>

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

#include "config/config.hpp"
#include "internal/graphics/graphics.hpp"
#include "internal/matrix/matrix.hpp"
#include "internal/keycode/handler.hpp"

std::vector<uint8_t> columns = MATRIX_COLUMNS;
std::vector<uint8_t> rows = MATRIX_ROWS;

Matrix matrix(columns, rows);

void setup() {
    #ifdef DISPLAY_ENABLED
    gfx_init();
    #endif
    usb_init();
}

void loop() {
    matrix.scan();
    uint16_t state = matrix.state();
    handle_state(state, matrix.size());

    #ifdef DISPLAY_ENABLED
    gfx_flush();
    #endif
}
