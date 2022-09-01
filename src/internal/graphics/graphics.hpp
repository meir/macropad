
#pragma once

#include <Arduino.h>

#include "../../config/config.hpp"
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <Adafruit_NeoPixel.h>

#ifndef DISPLAY_WIDTH
#define DISPLAY_WIDTH 135
#endif

#ifndef DISPLAY_HEIGHT
#define DISPLAY_HEIGHT 240
#endif

#ifndef DISPLAY_ROTATION
#define DISPLAY_ROTATION 2
#endif

#ifndef DISPLAY_BACKGROUND_COLOR
#define DISPLAY_BACKGROUND_COLOR 0x0000
#endif

#ifndef DISPLAY_FOREGROUND_COLOR
#define DISPLAY_FOREGROUND_COLOR 0xFFFF
#endif

void gfx_init();
void gfx_flush();

void gfx_set_led(uint16_t index, uint32_t color) __attribute__ ((weak));
Adafruit_NeoPixel pixels() __attribute__ ((weak));

void task_user_gfx_init() __attribute__ ((weak));

GFXcanvas16* get_canvas();
Adafruit_ST7789* get_tft();