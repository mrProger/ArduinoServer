#ifndef ARDUINOSERVER_DISPLAY_H
#define ARDUINOSERVER_DISPLAY_H

#include <Adafruit_ST7735.h>

class Display {
public:
    Adafruit_ST7735* display;
    uint16_t bg_color = ST7735_BLACK;
    uint16_t fg_color = ST7735_WHITE;

    Display(int8_t tft_cs, int8_t tft_dc, int8_t tft_mosi, int8_t tft_sclk, int8_t tft_rst);
    void Init();
    void Write(const char* text);
    void WriteLine(const char* text);
    void WriteOnPos(const char* text, int16_t x, int16_t y);
    void Clear();
    void SetBackgroundColor(uint16_t color);
    void SetForegroundColor(uint16_t color);
};


#endif //ARDUINOSERVER_DISPLAY_H
