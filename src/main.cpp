
#include <Arduino.h>
#include <vector>

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <thread>

#include "config/config.hpp"
#include "internal/graphics/graphics.hpp"
#include "internal/matrix/matrix.hpp"
#include "internal/keycode/handler.hpp"

std::vector<uint8_t> columns = MATRIX_COLUMNS;
std::vector<uint8_t> rows = MATRIX_ROWS;

Matrix matrix(columns, rows);

std::thread thread_matrix;
std::thread thread_user_tasks;

void matrix_loop() {
    while (true) {
        matrix.scan();
        uint16_t state = matrix.state();
        handle_state(state, matrix.size());
    }
}

void user_tasks_loop() {
    while (true) {
        handle_user_tasks();
        gfx_flush();
    }
}

void setup() {
    #ifdef DISPLAY_ENABLED
    gfx_init();
    #endif

    usb_init();
}

void loop() {
    thread_user_tasks = std::thread(user_tasks_loop);
    thread_matrix = std::thread(matrix_loop);

    thread_user_tasks.join();
    thread_matrix.join();
}
