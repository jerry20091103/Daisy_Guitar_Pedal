#include "main_window.h"
#include "display.h"

main_window main_window_ins;

void main_window::draw()
{
    u8g2.setFont(u8g2_font_6x12_mr);
    u8g2.drawStr(1, 9, "Main Window");
    u8g2.setFont(u8g2_font_5x8_mr);
    u8g2.drawStr(1, 63, "Main Window");
    if (state)
    {
        u8g2.setDrawColor(1);
        u8g2.drawCircle(63, 31, 10);
    }
    else
    {
        u8g2.setDrawColor(1);
        u8g2.drawCircle(63, 31, 5);
    }
}

void main_window::update()
{
    time++;
    if(time >= 10)
    {
        time = 0;
        state = !state;
    }
}

all_windows main_window::get_window_id()
{
    return MAIN_WINDOW;
}

void main_window::on_btn_pressed(int id)
{

}

void main_window::on_btn_holded(int id)
{

}