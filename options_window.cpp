#include "options_window.h"
#include "display.h"
#include "command.h"
#include "memory.h"
#include "effects_rack.h"

options_window options_window_ins;

void options_window::draw()
{
    // Draw topic and bottom text boxes
    u8g2.setDrawColor(1);
    u8g2.drawBox(0, 0, 128, 10);
    u8g2.drawBox(0, 55, 128, 9);

    // Draw option names and values
    u8g2.setFont(u8g2_font_profont10_mr);
    for (uint8_t i = cur_page * 4; i < OPTIONS_AMOUNT && i < cur_page * 4 + 4; i++)
    {
        unsigned char pos = i % 4;
        if (i == cur_option)
        {
            u8g2.setDrawColor(0);
            draw_option(i, pos);
            u8g2.setDrawColor(1);
            u8g2.drawVLine(23, 12 + 11 * pos, 9);
        }
        else
        {
            draw_option(i, pos);
        }
    }
    // Draw page number
    u8g2.setFont(u8g2_font_6x12_mr);
    u8g2.setCursor(1, 35);
    u8g2.print(cur_page + 1);
    u8g2.drawStr(7, 35, "/");
    u8g2.setCursor(13, 35);
    u8g2.print(OPTIONS_AMOUNT / 5 + 1);

    // Draw page arrows
    for (uint8_t i = 0; i <= 3; i++)
    {
        u8g2.drawPixel(10 - i, 16 + i - page_arrow_state);
        u8g2.drawPixel(10 + i, 16 + i - page_arrow_state);
    }
    for (uint8_t i = 0; i <= 3; i++)
    {
        u8g2.drawPixel(10 - i, 48 - i + page_arrow_state);
        u8g2.drawPixel(10 + i, 48 - i + page_arrow_state);
    }
    // Draw topic
    u8g2.setDrawColor(0);
    u8g2.drawStr(1, 8, "Options:");
    // Draw bottom text
    u8g2.setFont(u8g2_font_5x8_mr);
    u8g2.drawStr(1, 62, "BACK/----  |  SELECT/----");

    // Draw 8x8 matrix
    u8g2_8x8.setFont(u8g2_font_open_iconic_embedded_1x_t);
    u8g2_8x8.drawGlyph(0, 8, 72);
}

void options_window::draw_option(unsigned char id, unsigned char pos)
{
    switch (id)
    {
    case OPT_SAVE_FLASH:
        u8g2.drawStr(24, 19 + 11 * pos, "Save to flash memory");
        break;
    case OPT_LED_BRIGHTNESS:
        u8g2.drawStr(24, 19 + 11 * pos, "LED Brightness");
        u8g2.drawStr(103, 19 + 11 * pos, "<  >");
        u8g2.setCursor(109, 19 + 11 * pos);
        u8g2.print((unsigned char)(led_lvl / 25));
        break;

    case OPT_DELAY_UNIT:
        u8g2.drawStr(24, 19 + 11 * pos, "Delay time unit");
        u8g2.drawStr(103, 19 + 11 * pos, "<   >");
        u8g2.setCursor(109, 19 + 11 * pos);
        if(delay_ms)
            u8g2.print("MS");
        else
            u8g2.print("BPM");

        break;

    default:
        break;
    }
}

void options_window::update()
{
    // Update animations
    time++;
    if (time > 3)
    {
        page_arrow_state = !page_arrow_state;
        time = 0;
    }
    // Update page
    cur_page = cur_option / 4;
}

all_windows options_window::get_window_id()
{
    return OPTIONS_WINDOW;
}

void options_window::on_btn_pressed(buttons id)
{
    switch (id)
    {
    case BTN_LEFT:
        cmd_type[(cmd_pos + cmd_count) % MAX_COMMAND_BUF] = CMD_UI_OPT_PAGE_UP;
        cmd_count++;
        break;

    case BTN_RIGHT:
        cmd_type[(cmd_pos + cmd_count) % MAX_COMMAND_BUF] = CMD_UI_OPT_PAGE_DOWN;
        cmd_count++;
        break;

    case BTN_UP:
        cmd_type[(cmd_pos + cmd_count) % MAX_COMMAND_BUF] = CMD_UI_OPT_CUR_UP;
        cmd_count++;
        break;

    case BTN_DOWN:
        cmd_type[(cmd_pos + cmd_count) % MAX_COMMAND_BUF] = CMD_UI_OPT_CUR_DOWN;
        cmd_count++;
        break;

    case BTN_OK:
        cmd_type[(cmd_pos + cmd_count) % MAX_COMMAND_BUF] = CMD_OPT_SELECT;
        cmd_count++;
        break;
    
    case BTN_ENCODER:
        cmd_type[(cmd_pos + cmd_count) % MAX_COMMAND_BUF] = CMD_UI_OPT_BACK;
        cmd_count++;
        break;

    default:
        break;
    }
}

void options_window::on_btn_holded(buttons id)
{
    switch (id)
    {

    default:
        break;
    }
}

void options_window::on_enc_turned(RotaryEncoder::Direction dir)
{
    switch (dir)
    {
    case ENCODER_CW:
        cmd_type[(cmd_pos + cmd_count) % MAX_COMMAND_BUF] = CMD_OPT_INC;
        cmd_count++;
        break;

    case ENCODER_CCW:
        cmd_type[(cmd_pos + cmd_count) % MAX_COMMAND_BUF] = CMD_OPT_DEC;
        cmd_count++;
        break;

    default:
        break;
    }
}

void options_window::read_options()
{
    for (unsigned char i = 0; i < OPTIONS_AMOUNT; i++)
    {
        switch (i)
        {
        case OPT_LED_BRIGHTNESS:
            led_lvl = memory.options_mem[OPT_LED_BRIGHTNESS];
            u8g2_8x8.setContrast(led_lvl);
            break;
        
        case OPT_DELAY_UNIT:
            delay_ms = memory.options_mem[OPT_DELAY_UNIT];
            effects_rack.effects_arr[DELAY_MOD_ID]->set_param(0, effects_rack.effects_arr[DELAY_MOD_ID]->param[0].value);

        default:
            break;
        }
    }
}

void options_window::save_options()
{
    for (unsigned char i = 0; i < OPTIONS_AMOUNT; i++)
    {
        switch (i)
        {
        case OPT_LED_BRIGHTNESS:
            memory.options_mem[i] = led_lvl;
            break;
        
        case OPT_DELAY_UNIT:
            memory.options_mem[i] = delay_ms;
            break;

        default:
            memory.options_mem[i] = 0;
            break;
        }
    }
}