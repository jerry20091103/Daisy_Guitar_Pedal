#ifndef EFFECT_SELECT_WINDOW_H
#define EFFECT_SELECT_WINDOW_H

#include "windows.h"

// Main Window class
class effect_select_window : public windows
{
public:
    virtual void draw() override;
    virtual void update() override;
    virtual all_windows get_window_id() override;
    virtual void on_btn_pressed(buttons id) override;
    virtual void on_btn_holded(buttons id) override;
    virtual void on_enc_turned(RotaryEncoder::Direction dir) override;
    uint8_t cur_effect = 0;
    uint8_t cur_page = 0;

private:
    int time = 0;
    bool page_arrow_state = false;
};

// create a single instance
extern effect_select_window effect_select_window_ins;

#endif