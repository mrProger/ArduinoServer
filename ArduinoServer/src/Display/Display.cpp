#include "Display.h"

Display::Display(int8_t tft_cs, int8_t tft_dc, int8_t tft_mosi, int8_t tft_sclk, int8_t tft_rst) {
    this->cs = tft_cs;
    this->dc = tft_dc;
    this->mosi = tft_mosi;
    this->sclk = tft_sclk;
    this->rst = tft_rst;

    this->display = new Adafruit_ST7735(cs, dc, mosi, sclk, rst);
}

void Display::Init() {
    this->display->initR(INITR_BLACKTAB);
}

void Display::Write(const char* text) {
    this->display->setTextColor(this->fg_color);
    this->display->setTextWrap(true);
    this->display->print(text);
}

void Display::WriteLine(const char* text) {
    this->display->setTextColor(this->fg_color);
    this->display->setTextWrap(true);
    this->display->println(text);
}

void Display::WriteOnPos(const char* text, int16_t x, int16_t y) {
    this->display->setCursor(x, y);
    this->display->setTextColor(this->fg_color);
    this->display->setTextWrap(true);
    this->display->print(text);
}

void Display::Clear() {
    this->display->fillScreen(this->bg_color);
}

void Display::SetBackgroundColor(uint16_t color) {
    this->bg_color = color;
}

void Display::SetForegroundColor(uint16_t color) {
    this->fg_color = color;
}