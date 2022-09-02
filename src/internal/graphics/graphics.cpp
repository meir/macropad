
#include "graphics.hpp"

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
GFXcanvas16 canvas(DISPLAY_WIDTH, DISPLAY_HEIGHT);

#ifdef NEOPIXEL_ENABLED
Adafruit_NeoPixel neopixel(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
#endif

void gfx_init() {
    #ifndef BACKLIGHT_OFF
        pinMode(TFT_BACKLITE, OUTPUT);
        digitalWrite(TFT_BACKLITE, HIGH);
    #endif

    pinMode(TFT_I2C_POWER, OUTPUT);
    digitalWrite(TFT_I2C_POWER, HIGH);
    delay(10);

    tft.init(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    tft.setRotation(DISPLAY_ROTATION);
    tft.setRotation(2);

    #ifdef NEOPIXEL_ENABLED
        neopixel.begin();
    #endif

    canvas.setCursor(0, 0);
    canvas.fillScreen(DISPLAY_BACKGROUND_COLOR);
    canvas.setTextColor(DISPLAY_FOREGROUND_COLOR);
    gfx_flush();
}

void gfx_flush() {
    tft.drawRGBBitmap(0, 0, canvas.getBuffer(), canvas.width(), canvas.height());
    canvas.setCursor(0, 0);
    canvas.fillScreen(DISPLAY_BACKGROUND_COLOR);
}

void gfx_backlight(bool state) {
    digitalWrite(TFT_BACKLITE, state ? HIGH : LOW);
}

void gfx_display(bool state) {
    digitalWrite(TFT_I2C_POWER, state ? HIGH : LOW);
}

#ifdef NEOPIXEL_ENABLED
void gfx_set_led(uint16_t index, uint32_t color) {
    neopixel.setPixelColor(index, color);
    neopixel.show();
}

void gfx_clear_leds() {
    neopixel.clear();
    neopixel.show();
}

Adafruit_NeoPixel pixels() {
    return neopixel;
}
#endif

GFXcanvas16* get_canvas() {
    return &canvas;
}

Adafruit_ST7789* get_tft() {
    return &tft;
}
