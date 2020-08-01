#ifndef CONTROLS_H
#define CONTROLS_H

#include <EasyButton.h>
#include <RotaryEncoder.h>

#define BTN_HOLD_TIME 800
#define ENCODER_CW RotaryEncoder::Direction::CLOCKWISE
#define ENCODER_CCW RotaryEncoder::Direction::COUNTERCLOCKWISE
#define ENCODER_NOTURN RotaryEncoder::Direction::NOROTATION

extern EasyButton btn[10];
enum buttons : byte
{
    BTN_ENCODER, // pin 17 #0
    BTN_FS0,     // pin 18 #1
    BTN_FS1,     // pin 19 #2
    BTN_FS2,     // pin 21 #3
    BTN_FS3,     // pin 22 #4
    BTN_LEFT,    // pin 26 #5
    BTN_RIGHT,   // pin 27 #6
    BTN_UP,      // pin 28 #7
    BTN_DOWN,    // pin 29 #8
    BTN_OK       // pin 30 #9
};

extern RotaryEncoder encoder;

class _controls
{
public:
    void init();
    void btn_update();

private:
};

// A lot of call back functions...
void btn0_press();
void btn1_press();
void btn2_press();
void btn3_press();
void btn4_press();
void btn5_press();
void btn6_press();
void btn7_press();
void btn8_press();
void btn9_press();

void btn0_hold();
void btn1_hold();
void btn2_hold();
void btn3_hold();
void btn4_hold();
void btn5_hold();
void btn6_hold();
void btn7_hold();
void btn8_hold();
void btn9_hold();

void btn0_int();
void btn1_int();
void btn2_int();
void btn3_int();
void btn4_int();
void btn5_int();
void btn6_int();
void btn7_int();
void btn8_int();
void btn9_int();

// encoder interrupt
void encoder_interrupt();

// A single instance of controls
extern _controls controls;

#endif