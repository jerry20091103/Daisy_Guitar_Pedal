#ifndef WINDOWS_H
#define WINDOWS_H

#include "controls.h"

#define MAX_WINDOWS_NUM 5

enum all_windows : byte
{
    MAIN_WINDOW,
    MSG_WINDOW,
    EFFECT_PARAM_WINDOW,
    EFFECT_SELECT_WINDOW,
    OPTIONS_WINDOW
};

class windows
{
public:
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual all_windows get_window_id() = 0;
    virtual void on_btn_pressed(buttons id) = 0;
    virtual void on_btn_holded(buttons id) = 0;
    virtual void on_enc_turned(RotaryEncoder::Direction dir) = 0;

private:
};

#endif
