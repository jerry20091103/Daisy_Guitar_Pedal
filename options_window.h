#ifndef OPTIONS_WINDOW_H
#define OPTIONS_WINDOW_H

#include "windows.h"

#define OPTIONS_AMOUNT 2

enum all_options : unsigned char
{
    OPT_SAVE_FLASH,
    OPT_LED_BRIGHTNESS
};

// Options Window class
class options_window : public windows
{
public:
    virtual void draw() override;
    virtual void update() override;
    virtual all_windows get_window_id() override;
    virtual void on_btn_pressed(buttons id) override;
    virtual void on_btn_holded(buttons id) override;
    virtual void on_enc_turned(RotaryEncoder::Direction dir) override;
    uint8_t cur_option = 0;
    uint8_t cur_page = 0;
    // option values
    unsigned char led_lvl = 25;

private:
    void draw_option(unsigned char id, unsigned char pos);
    int time = 0;
    bool page_arrow_state = false;
};

// create a single instance
extern options_window options_window_ins;

#endif