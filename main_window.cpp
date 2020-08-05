#include "main_window.h"
#include "display.h"
#include "command.h"
#include "effects_rack.h"

main_window main_window_ins;

void main_window::draw()
{
    // Draw topic and bottom text boxes
    u8g2.setDrawColor(1);
    u8g2.drawBox(0, 0, 128, 10);
    u8g2.drawBox(0, 55, 128, 9);

    // Draw effect boxes
    u8g2.drawRFrame(6, 20, 20, 30, 3);
    u8g2.drawRFrame(30, 20, 20, 30, 3);
    u8g2.drawRFrame(54, 20, 20, 30, 3);
    u8g2.drawRFrame(78, 20, 20, 30, 3);
    u8g2.drawRFrame(102, 20, 20, 30, 3);

    // Draw signal arrows
    u8g2.drawHLine(7, 35, 114);
    for (uint8_t i = 27; i < 100; i += 24)
    {
        u8g2.drawPixel(i, 34);
        u8g2.drawPixel(i + 1, 33);
        u8g2.drawPixel(i, 36);
        u8g2.drawPixel(i + 1, 37);
    }

    // Draw effect short name and footswitch
    u8g2.setFont(u8g2_font_profont10_mr);
    if (!cur_page)
    {
        for (uint8_t i = 0; i < 5; i++)
        {
            // get effect short name
            char name[5] = "----";
            if (signal_chain[i] != nullptr)
                strcpy(name, signal_chain[i]->effect_short_name);
            uint8_t pos = i % 5;
            uint8_t sel_pos = cur_effect % 5;
            if (pos == sel_pos)
            {
                u8g2.setDrawColor(0);
                u8g2.drawStr(102 - pos * 24, 18, name);
                u8g2.setDrawColor(1);
            }
            else
            {
                u8g2.drawStr(102 - pos * 24, 18, name);
            }
            // draw footswitch
            if (signal_chain[i] != nullptr && signal_chain[i]->enable)
            {
                u8g2.drawRBox(104 - pos * 24, 37, 16, 11, 3);
            }
            else
            {
                u8g2.drawRFrame(104 - pos * 24, 37, 16, 11, 3);
            }
        }
    }
    else
    {
        for (uint8_t i = 5; i < MAX_EFFECTS_NUM; i++)
        {
            // get effect short name
            char name[5] = "----";
            if (signal_chain[i] != nullptr)
                strcpy(name, signal_chain[i]->effect_short_name);
            uint8_t pos = i % 5;
            uint8_t sel_pos = cur_effect % 5;
            if (pos == sel_pos)
            {
                u8g2.setDrawColor(0);
                u8g2.drawStr(102 - pos * 24, 18, name);
                u8g2.setDrawColor(1);
            }
            else
            {
                u8g2.drawStr(102 - pos * 24, 18, name);
            }
            // draw footswitch
            if (signal_chain[i] != nullptr && signal_chain[i]->enable)
            {
                u8g2.drawRBox(104 - pos * 24, 37, 16, 11, 3);
            }
            else
            {
                u8g2.drawRFrame(104 - pos * 24, 37, 16, 11, 3);
            }
        }
    }

    // Draw left right arrows
    if (!cur_page)
    {
        u8g2.drawTriangle(0, 35, 4, 31, 4, 39);
    }
    else
    {
        u8g2.drawTriangle(128, 35, 124, 31, 124, 39);
    }

    // Draw effect numbers
    u8g2.setFont(u8g2_font_6x12_mr);
    if (!cur_page)
    {
        u8g2.drawStr(13, 32, "4");
        u8g2.drawStr(37, 32, "3");
        u8g2.drawStr(61, 32, "2");
        u8g2.drawStr(85, 32, "1");
        u8g2.drawStr(109, 32, "0");
    }
    else
    {
        u8g2.drawStr(13, 32, "9");
        u8g2.drawStr(37, 32, "8");
        u8g2.drawStr(61, 32, "7");
        u8g2.drawStr(85, 32, "6");
        u8g2.drawStr(109, 32, "5");
    }

    // Draw topic
    u8g2.setDrawColor(0);
    u8g2.drawStr(1, 8, "Preset 0");
    // Draw bottom text
    u8g2.setFont(u8g2_font_5x8_mr);
    u8g2.drawStr(1, 62, "ON OFF/OPTION | ENTER/DEL");

    // Draw 8x8 matrix
    u8g2_8x8.drawCircle(3, 3, 3);
}

void main_window::update()
{
    if (cur_effect < 5)
        cur_page = 0;
    else
        cur_page = 1;
}

all_windows main_window::get_window_id()
{
    return MAIN_WINDOW;
}

void main_window::on_btn_pressed(buttons id)
{
    switch (id)
    {
    case BTN_LEFT:
        cmd_type[(cmd_pos + cmd_count) % MAX_COMMAND_BUF] = CMD_UI_SIG_CUR_LEFT;
        cmd_count++;
        break;

    case BTN_RIGHT:
        cmd_type[(cmd_pos + cmd_count) % MAX_COMMAND_BUF] = CMD_UI_SIG_CUR_RIGHT;
        cmd_count++;
        break;

    case BTN_OK:
        cmd_type[(cmd_pos + cmd_count) % MAX_COMMAND_BUF] = CMD_UI_SIG_CUR_SELECT;
        cmd_count++;
        break;

    case BTN_ENCODER:
        cmd_type[(cmd_pos + cmd_count) % MAX_COMMAND_BUF] = CMD_UI_SIG_CUR_ONOFF;
        cmd_count++;
        break;

    default:
        break;
    }
}

void main_window::on_btn_holded(buttons id)
{
    switch (id)
    {
    case BTN_OK:
        cmd_type[(cmd_pos + cmd_count) % MAX_COMMAND_BUF] = CMD_UI_SIG_CUR_DEL;
        cmd_count++;
        break;
    
    default:
        break;
    }
}

void main_window::on_enc_turned(RotaryEncoder::Direction dir)
{
}