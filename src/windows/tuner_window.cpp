#include "src/display.h"
#include "src/command.h"
#include "tuner_window.h"
#include "src/tuner.h"

tuner_window tuner_window_ins;

void tuner_window::draw()
{
    // Draw topic and bottom text boxes
    u8g2.setDrawColor(1);
    u8g2.drawBox(0, 0, 128, 10);
    u8g2.drawBox(0, 55, 128, 9);

    // Draw frequency
    u8g2.setCursor(2, 51);
    u8g2.setFont(u8g2_font_helvB24_tn);
    u8g2.print(frequency, 2);


    // Draw topic
    u8g2.setDrawColor(0);
    u8g2.setFont(u8g2_font_6x12_mr);
    u8g2.drawStr(1, 8, "Tuner");
    // Draw bottom text
    u8g2.setFont(u8g2_font_profont10_mr);
    u8g2.drawStr(1, 62, "  BACK/---- | ----/----  ");
}

void tuner_window::update()
{
    float temp = tuner.get_frequency();
    if(temp < 5000)
        frequency = tuner.get_frequency();
}

all_windows tuner_window::get_window_id()
{
    return TUNER_WINDOW;
}

void tuner_window::on_btn_pressed(buttons id)
{
    switch (id)
    {
    case BTN_ENCODER:
        insert_command(CMD_LOOPER_BACK);
        break;
    
    default:
        break;
    }

}

void tuner_window::on_btn_holded(buttons id)
{
    switch (id)
    {
    case BTN_FS0:
        insert_command(CMD_LOOPER_BACK);
        break;

    default:
        break;
    }
}

void tuner_window::on_enc_turned(RotaryEncoder::Direction dir)
{

}