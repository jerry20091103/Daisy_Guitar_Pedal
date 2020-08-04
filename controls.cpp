#include "controls.h"
#include "display.h"

EasyButton btn[10]{17, 18, 19, 21, 22, 26, 27, 28, 29, 30};
RotaryEncoder encoder(15, 16);

_controls controls;

void _controls::init()
{
    // Initialize buttons
    for (int i = 0; i < 10; i++)
        btn[i].begin();
    btn[0].onPressed(btn0_press);
    btn[0].onPressedFor(BTN_HOLD_TIME, btn0_hold);
    btn[0].enableInterrupt(btn0_int);

    btn[1].onPressed(btn1_press);
    btn[1].onPressedFor(BTN_HOLD_TIME, btn1_hold);
    btn[1].enableInterrupt(btn1_int);

    btn[2].onPressed(btn2_press);
    btn[2].onPressedFor(BTN_HOLD_TIME, btn2_hold);
    btn[2].enableInterrupt(btn2_int);

    btn[3].onPressed(btn3_press);
    btn[3].onPressedFor(BTN_HOLD_TIME, btn3_hold);
    btn[3].enableInterrupt(btn3_int);

    btn[4].onPressed(btn4_press);
    btn[4].onPressedFor(BTN_HOLD_TIME, btn4_hold);
    btn[4].enableInterrupt(btn4_int);

    btn[5].onPressed(btn5_press);
    btn[5].onPressedFor(BTN_HOLD_TIME, btn5_hold);
    btn[5].enableInterrupt(btn5_int);

    btn[6].onPressed(btn6_press);
    btn[6].onPressedFor(BTN_HOLD_TIME, btn6_hold);
    btn[6].enableInterrupt(btn6_int);

    btn[7].onPressed(btn7_press);
    btn[7].onPressedFor(BTN_HOLD_TIME, btn7_hold);
    btn[7].enableInterrupt(btn7_int);

    btn[8].onPressed(btn8_press);
    btn[8].onPressedFor(BTN_HOLD_TIME, btn8_hold);
    btn[8].enableInterrupt(btn8_int);

    btn[9].onPressed(btn9_press);
    btn[9].onPressedFor(BTN_HOLD_TIME, btn9_hold);
    btn[9].enableInterrupt(btn9_int);

    // Initialize encoder
    attachInterrupt(digitalPinToInterrupt(15), encoder_interrupt, CHANGE);
    attachInterrupt(16, encoder_interrupt, CHANGE);
}

void _controls::btn_update()
{
    for (int i = 0; i < 10; i++)
    {
        btn[i].update();
    }
}

// press
void btn0_press()
{
    display.current_window->on_btn_pressed(BTN_ENCODER);
}
void btn1_press()
{
    display.current_window->on_btn_pressed(BTN_FS0);
}
void btn2_press()
{
    display.current_window->on_btn_pressed(BTN_FS1);
}
void btn3_press()
{
    display.current_window->on_btn_pressed(BTN_FS2);
}
void btn4_press()
{
    display.current_window->on_btn_pressed(BTN_FS3);
}
void btn5_press()
{
    display.current_window->on_btn_pressed(BTN_LEFT);
}
void btn6_press()
{
    display.current_window->on_btn_pressed(BTN_RIGHT);
}
void btn7_press()
{
    display.current_window->on_btn_pressed(BTN_UP);
}
void btn8_press()
{
    display.current_window->on_btn_pressed(BTN_DOWN);
}
void btn9_press()
{
    display.current_window->on_btn_pressed(BTN_OK);
}

// hold
void btn0_hold()
{
    display.current_window->on_btn_holded(BTN_ENCODER);
}
void btn1_hold()
{
    display.current_window->on_btn_holded(BTN_FS0);
}
void btn2_hold()
{
    display.current_window->on_btn_holded(BTN_FS1);
}
void btn3_hold()
{
    display.current_window->on_btn_holded(BTN_FS2);
}
void btn4_hold()
{
    display.current_window->on_btn_holded(BTN_FS3);
}
void btn5_hold()
{
    display.current_window->on_btn_holded(BTN_LEFT);
}
void btn6_hold()
{
    display.current_window->on_btn_holded(BTN_RIGHT);
}
void btn7_hold()
{
    display.current_window->on_btn_holded(BTN_UP);
}
void btn8_hold()
{
    display.current_window->on_btn_holded(BTN_DOWN);
}
void btn9_hold()
{
    display.current_window->on_btn_holded(BTN_OK);
}

// interrupt
void btn0_int()
{
    btn[0].read();
}
void btn1_int()
{
    btn[1].read();
}
void btn2_int()
{
    btn[2].read();
}
void btn3_int()
{
    btn[3].read();
}
void btn4_int()
{
    btn[4].read();
}
void btn5_int()
{
    btn[5].read();
}
void btn6_int()
{
    btn[6].read();
}
void btn7_int()
{
    btn[7].read();
}
void btn8_int()
{
    btn[8].read();
}
void btn9_int()
{
    btn[9].read();
}

// Encoder interrupt
void encoder_interrupt()
{
    RotaryEncoder::Direction dir;
    encoder.tick();
    dir = encoder.getDirection();
    if(dir != ENCODER_NOTURN)
    {
        display.current_window->on_enc_turned(dir);
    }
}