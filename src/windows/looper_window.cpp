#include "looper_window.h"
#include "src/display.h"
#include "src/command.h"
#include "src/effect_modules/effects_rack.h"
#include "src/looper.h"

looper_window looper_window_ins;

void looper_window::draw()
{
    // Draw topic and bottom text boxes
    u8g2.setDrawColor(1);
    u8g2.drawBox(0, 0, 128, 10);
    u8g2.drawBox(0, 55, 128, 9);
    
    // Draw loop progress bar
    u8g2.drawFrame(0, 11, 128, 12);
    u8g2.drawBox(2, 13, looper.get_loop_pos() * 124, 8);

    // Draw looper status
    // record
    if(looper.enable && looper.recording)
    {
        u8g2.drawDisc(14, 38, 10);
    }
    // play
    else if(looper.enable)
    {
        u8g2.drawTriangle(4, 28, 4, 48, 24, 38);
    }
    // stop
    else
    {
        u8g2.drawBox(5, 30, 18, 18);
    }

    // Draw layer number
    u8g2.setCursor(28, 51);
    u8g2.setFont(u8g2_font_helvB24_tn);
    u8g2.print(looper.cur_layer);
    u8g2.print("/");
    u8g2.print(looper.layer_count);

    // Draw topic
    u8g2.setDrawColor(0);
    u8g2.setFont(u8g2_font_6x12_mr);
    u8g2.drawStr(1, 8, "Looper");
    // Draw bottom text
    u8g2.setFont(u8g2_font_profont10_mr);
    u8g2.drawStr(1, 62, "  BACK/---- | ----/----  ");
    // Draw loop level
    u8g2.setCursor(66, 8);
    u8g2.print("lvl:");
    u8g2.print(looper.loop_level * 10, 0);
    // Draw memory usage
    u8g2.setCursor(98, 8);
    u8g2.print("(");
    u8g2.print(looper.get_meory_usage() * 100, 0);
    u8g2.print("%)");

    // Draw 8x8 matrix
    u8g2_8x8.setFont(u8g2_font_profont10_mr);
    u8g2_8x8.setCursor(2, 6);
    u8g2_8x8.print(effects_rack.cur_preset);
}

void looper_window::update()
{
    
}

all_windows looper_window::get_window_id()
{
    return LOOPER_WINDOW;
}

void looper_window::on_btn_pressed(buttons id)
{
    switch (id)
    {
    case BTN_ENCODER:
        insert_command(CMD_LOOPER_BACK);
        break;
    
    case BTN_FS0:
        insert_command(CMD_UI_PRESET_UP);
        break;

    case BTN_FS1:
        insert_command(CMD_UI_PRESET_DOWN);
        break;
    
    case BTN_UP:
        insert_command(CMD_LOOPER_LVL_INC);
        break;
    
    case BTN_DOWN:
        insert_command(CMD_LOOPER_LVL_DEC);
        break;
    
    case BTN_LEFT:
        insert_command(CMD_LOOPER_POS_START);
        break;
        
    default:
        break;
    }
    
}

void looper_window::on_btn_holded(buttons id)
{
    
}

void looper_window::on_enc_turned(RotaryEncoder::Direction dir)
{
    switch (dir)
    {
    case ENCODER_CW:
        insert_command(CMD_LOOPER_POS_INC);
        break;

    case ENCODER_CCW:
        insert_command(CMD_LOOPER_POS_DEC);
        break;

    default:
        break;
    }
}