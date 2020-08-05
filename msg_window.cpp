#include "msg_window.h"
#include "display.h"

msg_window msg_window_ins;

char msg1[MAX_MSG_LEN + 1] = "--Empty--";
char msg2[MAX_MSG_LEN + 1] = "--Empty--";
_msg_type msg_type = MSG_INFO;
int msg_popup_time = 20;

void show_msg(_msg_type type, int time, char *data1, char *data2)
{
    strncpy(msg1, data1, MAX_MSG_LEN);
    strncpy(msg2, data2, MAX_MSG_LEN);
    msg_popup_time = time;
    msg_type = type;
    display.change_window(MSG_WINDOW);
}

void msg_window::draw()
{
    u8g2.setDrawColor(1);
    // Draw outer frame
    u8g2.drawFrame(0, 0, 128, 64);
    // Draw message content
    u8g2.setFont(u8g2_font_6x12_mr);
    u8g2.drawStr(4, 35, msg1);
    u8g2.drawStr(4, 50, msg2);
    // Draw message type
    u8g2.setDrawColor(0);
    u8g2.setFont(u8g2_font_7x13_mr);
    switch (msg_type)
    {
    case MSG_INFO:
        u8g2.drawStr(4, 15, "INFO:");
        break;
    case MSG_WARNING:
        u8g2.drawStr(4, 15, "WARNING:");
        break;
    case MSG_ERROR:
        u8g2.drawStr(4, 15, "ERROR:");
    default:
        break;
    }
}

void msg_window::update()
{
    time++;
    if(time >= msg_popup_time)
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

void msg_window::on_enc_turned(RotaryEncoder::Direction dir)
{

}