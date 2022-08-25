
#include "graphics.hpp"

Adafruit_ST7789 _tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void gfx_init() {
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);

  pinMode(TFT_I2C_POWER, OUTPUT);
  digitalWrite(TFT_I2C_POWER, HIGH);
  delay(10);

  // initialize TFT
  _tft.init(135, 240); // Init ST7789 240x135
  _tft.setRotation(2);
  _tft.fillScreen(ST77XX_BLACK);
}

void gfx_reset() {
  _tft.setCursor(0, 0);
}

void gfx_draw() {
  gfx_reset();
}

void gfx_print(String text) {
  _tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  _tft.print(text);
}

void gfx_println(String text) {
  gfx_print(text + "\n");
}

Adafruit_ST7789 tft() {
  return _tft;
}