#include "display.h"

U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 8, /* data=*/ 9, /* CS=*/ 7, /* reset=*/ 6);
LedControl lc1=LedControl(9,8,5,1); 

_display display;

void _display::init()
{
    // Initialize 8x8 led matrix
    lc1.shutdown(0,false); //wake up the MAX72XX from power-saving mode
    lc1.setIntensity(0,8); //set a medium brightness for the Leds (maybe read from EEPROM later)
    // Initialize 128x64 lcd
    u8g2.begin();
    u8g2.clearBuffer();
    // Initialize windos list and the first window
    windows_arr[MAIN_WINDOW] = &main_window_ins;
    current_window = windows_arr[MAIN_WINDOW];
}

void _display::draw()
{
    current_window->update();
    //lc1.clearDisplay(0);
    u8g2.clearBuffer();
    current_window->draw();
    u8g2.sendBuffer();
}