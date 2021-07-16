#ifndef TUNER_WINDOW_H
#define TUNER_WINDOW_H

#include "windows.h"

// Tuner Window class
class tuner_window : public windows
{
public:
    virtual void draw() override;
    virtual void update() override;
    virtual all_windows get_window_id() override;
    virtual void on_btn_pressed(buttons id) override;
    virtual void on_btn_holded(buttons id) override;
    virtual void on_enc_turned(RotaryEncoder::Direction dir) override;
private:
    float frequency = 0;
};

// create a single instance
extern tuner_window tuner_window_ins;

#endif