#include "display.h"
#include "msg_window.h"
#include "main_window.h"
#include "effect_param_window.h"

U8G2_ST7920_128X64_F_HW_SPI u8g2(U8G2_R0, /* CS=*/ 7, /* reset=*/ 6);
U8G2_MAX7219_8X8_F_4W_SW_SPI u8g2_8x8(U8G2_R0, /* clock=*/ 3, /* data=*/ 5, /* cs=*/ 4, /* dc=*/ U8X8_PIN_NONE, /* reset=*/ U8X8_PIN_NONE);
Adafruit_MCP23017 mcp;

_display display;

void _display::init()
{
    // Initialize 8x8 led matrix
    u8g2_8x8.begin();
    u8g2_8x8.clearBuffer();
    u8g2_8x8.setContrast(20);
    // Initialize 128x64 lcd
    u8g2.setBusClock(2400000); // Set a higher clock for better performance
    u8g2.begin();
    u8g2.clearBuffer();
    // Initialize footswitch LEDs
    mcp.begin();
    for (uint8_t i = 0; i < 7; i++)
        mcp.pinMode(i, OUTPUT);
    mcp.pinMode(15, OUTPUT); // For relay
    // Initialize windos list and the first window
    windows_arr[MAIN_WINDOW] = &main_window_ins;
    windows_arr[MSG_WINDOW] = &msg_window_ins;
    windows_arr[EFFECT_PARAM_WINDOW] = &effect_param_window_ins;
    current_window = windows_arr[MAIN_WINDOW];
    last_window = windows_arr[MAIN_WINDOW];
}

void _display::draw()
{
    current_window->update();
    u8g2_8x8.clearBuffer();
    u8g2.clearBuffer();
    current_window->draw();
    u8g2_8x8.sendBuffer();
    u8g2.sendBuffer();
}

void _display::change_window(all_windows window)
{
    last_window = display.current_window;
    current_window = display.windows_arr[window];
}