#include "effect_select_window.h"
#include "display.h"
#include "command.h"
#include "effects_rack.h"

effect_select_window effect_select_window_ins;

void effect_select_window::draw()
{
    // Draw topic and bottom text boxes
    u8g2.setDrawColor(1);
    u8g2.drawBox(0, 0, 128, 10);
    u8g2.drawBox(0, 55, 128, 9);

    // Draw page number
    u8g2.setFont(u8g2_font_6x12_mr);
    u8g2.drawStr(2, 35, "1/5");

    // Draw page arrows
    for (uint8_t i = 0; i <= 3; i++)
    {
        u8g2.drawPixel(11 - i, 16 + i - page_arrow_state);
        u8g2.drawPixel(11 + i, 16 + i - page_arrow_state);
    }
    for (uint8_t i = 0; i <= 3; i++)
    {
        u8g2.drawPixel(11 - i, 48 - i + page_arrow_state);
        u8g2.drawPixel(11 + i, 48 - i + page_arrow_state);
    }

    // Draw effect names
    //u8g2.drawStr()

    // Draw topic
    u8g2.setDrawColor(0);
    u8g2.drawStr(1, 8, "Select an effect:");
    // Draw bottom text
    u8g2.setFont(u8g2_font_5x8_mr);
    u8g2.drawStr(1, 62, " ----/---- | ENTER/CANCEL");
}

void effect_select_window::update()
{
    time++;
    if (time > 3)
    {
        page_arrow_state = !page_arrow_state;
        time = 0;
    }
}

all_windows effect_select_window::get_window_id()
{
    return EFFECT_SELECT_WINDOW;
}

void effect_select_window::on_btn_pressed(buttons id)
{
}

void effect_select_window::on_btn_holded(buttons id)
{
}

void effect_select_window::on_enc_turned(RotaryEncoder::Direction dir)
{
}