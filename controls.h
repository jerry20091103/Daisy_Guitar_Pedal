#ifndef CONTROLS_H
#define CONTROLS_H

#include <EasyButton.h>
#include <RotaryEncoder.h>

#define BTN_HOLD_TIME 800
#define ENCODER_CW RotaryEncoder::Direction::CLOCKWISE
#define ENCODER_CCW RotaryEncoder::Direction::COUNTERCLOCKWISE
#define ENCODER_NOTURN RotaryEncoder::Direction::NOROTATION

extern EasyButton btn[13];
enum buttons
{
    BTN_ENCODER, // pin 17 #0
    BTN_FS0,     // pin 18 #1
    BTN_FS1,     // pin 19 #2
    BTN_FS2,     // pin 20 #3
    BTN_FS3,     // pin 21 #4
    BTN_FS4,     // pin 22 #5
    BTN_FS5,     // pin 23 #6
    BTN_FS6,     // pin 24 #7
    BTN_LEFT,    // pin 25 #8
    BTN_RIGHT,   // pin 26 #9
    BTN_UP,      // pin 27 #10
    BTN_DOWN,    // pin 28 #11
    BTN_OK       // pin 1  #12
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
void btn10_press();
void btn11_press();
void btn12_press();

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
void btn10_hold();
void btn11_hold();
void btn12_hold();

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
void btn10_int();
void btn11_int();
void btn12_int();

// encoder interrupt
void encoder_interrupt();

// A single instance of controls
extern _controls controls;

#endif