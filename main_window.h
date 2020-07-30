#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "windows.h"

class main_window : public windows
{
public:
    virtual void draw() override;
    virtual void update() override;
    virtual void on_btn_pressed() override; // TBD
    virtual void on_btn_holded() override;  // TBD

private:
    int time = 0;
    bool state = false;
};

// create a single instance
extern main_window main_window_ins;

#endif