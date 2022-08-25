#pragma once

#include <Arduino.h>
#include <WString.h>

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789

void gfx_init();
void gfx_draw();
void gfx_print(String text);
void gfx_println(String text);
void gfx_reset();
Adafruit_ST7789 tft();
