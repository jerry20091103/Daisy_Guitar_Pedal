#include "effect_param_window.h"
#include "display.h"
#include "command.h"
#include "effects_rack.h"
#include "main_window.h"

effect_param_window effect_param_window_ins;

void effect_param_window::draw()
{
    unsigned char cur_effect = main_window_ins.cur_effect;

    // Draw topic and bottom text boxes
    u8g2.setDrawColor(1);
    u8g2.drawBox(0, 0, 128, 10);
    u8g2.drawBox(0, 55, 128, 9);

    // Draw lines between parameters
    u8g2.drawHLine(0, 32, 128);
    u8g2.drawVLine(42, 10, 45);
    u8g2.drawVLine(85, 10, 45);

    // Draw parameter values
    u8g2.setFont(u8g2_font_profont10_mr);
    // (0)
    if (signal_chain[cur_effect]->param[0].enable)
    {
        u8g2.setCursor(1, 29);
        u8g2.print(signal_chain[cur_effect]->param[0].true_val);
    }
    // (1)
    if (signal_chain[cur_effect]->param[1].enable)
    {
        u8g2.setCursor(1, 51);
        u8g2.print(signal_chain[cur_effect]->param[1].true_val);
    }
    // (2)
    if (signal_chain[cur_effect]->param[2].enable)
    {
        u8g2.setCursor(44, 29);
        u8g2.print(signal_chain[cur_effect]->param[2].true_val);
    }
    // (3)
    if (signal_chain[cur_effect]->param[3].enable)
    {
        u8g2.setCursor(44, 51);
        u8g2.print(signal_chain[cur_effect]->param[3].true_val);
    }
    // (4)
    if (signal_chain[cur_effect]->param[4].enable)
    {
        u8g2.setCursor(87, 29);
        u8g2.print(signal_chain[cur_effect]->param[4].true_val);
    }
    // (5)
    if (signal_chain[cur_effect]->param[5].enable)
    {
        u8g2.setCursor(87, 51);
        u8g2.print(signal_chain[cur_effect]->param[5].true_val);
    }

    // Draw parameter names
    u8g2.setFont(u8g2_font_profont10_mr);
    for (uint8_t i = 0; i < MAX_PARAM_NUM; i++)
    {
        if (signal_chain[cur_effect]->param[i].enable)
        {
            if (cur_param == i)
            {
                u8g2.setDrawColor(0);
                u8g2.drawStr(1 + (i / 2) * 43, 19 + (i % 2) * 22, signal_chain[cur_effect]->param[i].name);
                u8g2.setDrawColor(1);
            }
            else
                u8g2.drawStr(1 + (i / 2) * 43, 19 + (i % 2) * 22, signal_chain[cur_effect]->param[i].name);
        }
        else
        {
            if (cur_param == i)
            {
                u8g2.setDrawColor(0);
                u8g2.drawStr(1 + (i / 2) * 43, 19 + (i % 2) * 22, "----");
                u8g2.setDrawColor(1);
            }
            else
                u8g2.drawStr(1 + (i / 2) * 43, 19 + (i % 2) * 22, "----");
        }
    }

    // Draw topic
    u8g2.setFont(u8g2_font_6x12_mr);
    if (signal_chain[cur_effect]->enable)
    {
        u8g2.setDrawColor(0);
        u8g2.drawStr(1, 8, signal_chain[cur_effect]->effect_name);
    }
    else
    {
        u8g2.drawStr(1, 8, signal_chain[cur_effect]->effect_name);
        u8g2.setDrawColor(0);
        u8g2.drawVLine(0, 0, 10);
    }
    if (step_arrows_state)
    {
        u8g2.drawStr(107, 8, "<");
        u8g2.drawStr(121, 8, ">");
    }
    else
    {
        u8g2.drawStr(108, 8, "<");
        u8g2.drawStr(120, 8, ">");
    }
    u8g2.setCursor(114, 8);
    u8g2.print(cur_step);
    // Draw bottom text
    u8g2.setFont(u8g2_font_profont10_mr);
    u8g2.drawStr(1, 62, "ON OFF/STEP  |  BACK/----");

    // Draw 8x8 matrix
    u8g2_8x8.setFont(u8g2_font_profont10_mr);
    u8g2_8x8.setCursor(2, 6);
    u8g2_8x8.print(effects_rack.cur_preset);
}

void effect_param_window::update()
{
    time++;
    if (time > 2)
    {
        step_arrows_state = !step_arrows_state;
        time = 0;
    }
}

all_windows effect_param_window::get_window_id()
{
    return EFFECT_PARAM_WINDOW;
}

void effect_param_window::on_btn_pressed(buttons id)
{
    switch (id)
    {
    case BTN_LEFT:
        cmd_type[(cmd_pos + cmd_count) % MAX_COMMAND_BUF] = CMD_UI_PARAM_CUR_LEFT;
        cmd_count++;
        break;

    case BTN_RIGHT:
        cmd_type[(cmd_pos + cmd_count) % MAX_COMMAND_BUF] = CMD_UI_PARAM_CUR_RIGHT;
        cmd_count++;
        break;

    case BTN_UP:
        cmd_type[(cmd_pos + cmd_count) % MAX_COMMAND_BUF] = CMD_UI_PARAM_CUR_UP;
        cmd_count++;
        break;

    case BTN_DOWN:
        cmd_type[(cmd_pos + cmd_count) % MAX_COMMAND_BUF] = CMD_UI_PARAM_CUR_DOWN;
        cmd_count++;
        break;

    case BTN_OK:
        cmd_type[(cmd_pos + cmd_count) % MAX_COMMAND_BUF] = CMD_UI_PARAM_CUR_SELECT;
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

void effect_param_window::on_btn_holded(buttons id)
{
    switch (id)
    {
    case BTN_ENCODER:
        cmd_type[(cmd_pos + cmd_count) % MAX_COMMAND_BUF] = CMD_UI_PARAM_STEP;
        cmd_count++;
        break;

    default:
        break;
    }
}

void effect_param_window::on_enc_turned(RotaryEncoder::Direction dir)
{
    switch (dir)
    {
    case ENCODER_CW:
        cmd_type[(cmd_pos + cmd_count) % MAX_COMMAND_BUF] = CMD_EFFECTS_PARAM_INC;
        cmd_count++;
        break;

    case ENCODER_CCW:
        cmd_type[(cmd_pos + cmd_count) % MAX_COMMAND_BUF] = CMD_EFFECTS_PARAM_DEC;
        cmd_count++;
        break;

    default:
        break;
    }
}