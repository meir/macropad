
#include <Arduino.h>
#include "manager/manager.hpp"
#include "config/config.hpp"

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

#include "graphics/graphics.hpp"

Manager manager;

void setup() {
  gfx_init();
}

void loop() {
  manager.run();
}
