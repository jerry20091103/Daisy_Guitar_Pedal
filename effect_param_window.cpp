#include "effect_param_window.h"
#include "display.h"
#include "command.h"
#include "effects_rack.h"
#include "main_window.h"

effect_param_window effect_param_window_ins;

void effect_param_window::draw()
{
    // Draw topic and bottom text boxes
    u8g2.setDrawColor(1);
    u8g2.drawBox(0, 0, 128, 10);
    u8g2.drawBox(0, 55, 128, 9);

    // Draw parameter values
    u8g2.setFont(u8g2_font_6x12_mr);
    u8g2.drawStr(2, 29, "0*1234");
    u8g2.drawStr(2, 51, "567890");
    u8g2.drawStr(44, 29, "_.,*~`");
    u8g2.drawStr(86, 29, "123456");

    // Draw parameter names
    u8g2.setFont(u8g2_font_5x8_mr);
    u8g2.drawStr(2, 19, "abcdefgh");
    u8g2.drawStr(2, 41, "ijklmnop");
    u8g2.drawStr(44, 19, "qrstuvwx");
    u8g2.drawStr(86, 19, "yz_*-abc");

    // Draw topic
    u8g2.setDrawColor(0);
    u8g2.setFont(u8g2_font_6x12_mr);
    u8g2.drawStr(1, 8, signal_chain[main_window_ins.cur_effect]->effect_name);
    // Draw bottom text
    u8g2.setFont(u8g2_font_5x8_mr);
    u8g2.drawStr(1, 62, " ----/----  |  BACK/---- ");
    
}

void effect_param_window::update()
{

}

all_windows  effect_param_window::get_window_id() 
{
    return EFFECT_PARAM_WINDOW;
}

void effect_param_window::on_btn_pressed(buttons id)
{

}

void effect_param_window::on_btn_holded(buttons id)
{

}

void effect_param_window::on_enc_turned(RotaryEncoder::Direction dir)
{

}