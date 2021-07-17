#include "controls.h"
#include "display.h"
#include "command.h"

EasyButton btn[10]{17, 18, 19, 21, 22, 26, 27, 28, 29, 30};
RotaryEncoder encoder(15, 16);

_controls controls;

void _controls::init()
{
    // Initialize buttons
    for (int i = 0; i < 10; i++)
    {
        btn[i].begin();
        btn[i].onPressed(btn_press[i]);
        btn[i].onPressedFor(BTN_HOLD_TIME, btn_hold[i]);
        btn[i].enableInterrupt(btn_int[i]);
    }

    // Initialize encoder
    attachInterrupt(digitalPinToInterrupt(15), encoder_interrupt, CHANGE);
    attachInterrupt(digitalPinToInterrupt(16), encoder_interrupt, CHANGE);
}

void _controls::btn_update()
{
    for (int i = 0; i < 10; i++)
    {
        btn[i].update();
    }
}

btn_callback btn_press[10] = 
{
    btn0_press,
    btn1_press,
    btn2_press,
    btn3_press,
    btn4_press,
    btn5_press,
    btn6_press,
    btn7_press,
    btn8_press,
    btn9_press
};

btn_callback btn_hold[10] = 
{
    btn0_hold,
    btn1_hold,
    btn2_hold,
    btn3_hold,
    btn4_hold,
    btn5_hold,
    btn6_hold,
    btn7_hold,
    btn8_hold,
    btn9_hold,
};

btn_callback btn_int[10] = 
{
    btn0_int,
    btn1_int,
    btn2_int,
    btn3_int,
    btn4_int,
    btn5_int,
    btn6_int,
    btn7_int,
    btn8_int,
    btn9_int,
};

// press
void btn0_press()
{
    display.current_window->on_btn_pressed(BTN_ENCODER);
}
void btn1_press() // fs0
{
    display.current_window->on_btn_pressed(BTN_FS0);
}
void btn2_press() // fs1
{
    display.current_window->on_btn_pressed(BTN_FS1);
}
void btn3_press() // fs2 looper rec / redo
{
    insert_command(CMD_LOOPER_RECORD);
}
void btn4_press() // fs3 looper play/stop / undo / clear
{
    insert_command(CMD_LOOPER_STOP);
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
void btn3_hold() // fs2 looper rec / redo
{
    insert_command(CMD_LOOPER_REDO);
}
void btn4_hold() // fs3 looper play/stop / undo / clear
{
    insert_command(CMD_LOOPER_UNDO);
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