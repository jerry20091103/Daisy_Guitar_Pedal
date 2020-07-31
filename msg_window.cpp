#include "msg_window.h"
#include "display.h"

msg_window msg_window_ins;

char msg[MAX_MSG_LEN + 1] = "--Empty--";
_msg_type msg_type = MSG_INFO;

void msg_window::draw()
{
    // Draw message type
    u8g2.setFont(u8g2_font_7x13_mr);
    switch (msg_type)
    {
    case MSG_INFO:
        u8g2.drawStr(1, 13, "INFO:");
        break;
    case MSG_WARNING:
        u8g2.drawStr(1, 13, "WARNING:");
        break;
    case MSG_ERROR:
        u8g2.drawStr(1, 13, "ERROR:");
    default:
        break;
    }
    // Draw message content
    u8g2.setFont(u8g2_font_6x12_mr);
    u8g2.drawStr(1, 30, msg);
}

void msg_window::update()
{
    time++;
    if(time >= MSG_POPUP_TIME)
    {
        time = 0;
        display.change_window(display.last_window->get_window_id());
    }
}

all_windows msg_window::get_window_id()
{
    return MSG_WINDOW;
}

void msg_window::on_btn_pressed(buttons id)
{

}

void msg_window::on_btn_holded(buttons id)
{

}