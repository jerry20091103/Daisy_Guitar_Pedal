#ifndef DISPLAY_H
#define DISPLAY_H

#include <U8g2lib.h>
#include <Adafruit_MCP23017.h>
#include "windows.h"

extern U8G2_ST7920_128X64_F_HW_SPI u8g2;
extern U8G2_MAX7219_8X8_F_4W_SW_SPI u8g2_8x8;
extern Adafruit_MCP23017 mcp;

// A display class that combines the 128x64 lcd and 8x8 led matrix
class _display
{
public:
    void init();
    void draw();
    void change_window(all_windows window);
    windows *current_window;
    windows *last_window;
    windows *windows_arr[MAX_WINDOWS_NUM];
private:
};

// a single instance display
extern _display display;

#endif