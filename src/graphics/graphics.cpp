
#include "graphics.hpp"

Adafruit_ST7789 _tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
GFXcanvas16 _canvas(_tft.width(), _tft.height());

extern Adafruit_TestBed TB;

void gfx_init() {
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);

  pinMode(TFT_I2C_POWER, OUTPUT);
  digitalWrite(TFT_I2C_POWER, HIGH);
  delay(10);

  TB.neopixelPin = PIN_NEOPIXEL;
  TB.neopixelNum = 1; 
  TB.begin();
  TB.setColor(WHITE);

  // initialize TFT
  _tft.init(135, 240); // Init ST7789 240x135
  _tft.setRotation(2);
  _tft.setTextSize(2);
  _canvas.fillScreen(ST77XX_BLACK);
}

void gfx_reset() {
  _tft.drawRGBBitmap(0, 0, _canvas.getBuffer(), _canvas.width(), _canvas.height());
  _canvas.setCursor(0, 0);
  _canvas.fillScreen(ST77XX_BLACK);
}

void gfx_draw() {
  gfx_reset();
}

void gfx_print(String text) {
  _canvas.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  _canvas.print(text);
}

void gfx_println(String text) {
  gfx_print(text + "\n");
}

void led_setColor(uint32_t color) {
  TB.setColor(color);
}

GFXcanvas16 canvas() {
  return _canvas;
}

Adafruit_ST7789 tft() {
  return _tft;
}