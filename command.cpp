#include "command.h"
#include "display.h"
#include "main_window.h"
#include "effect_param_window.h"
#include "effect_select_window.h"
#include "msg_window.h"
#include "options_window.h"
#include "effects_rack.h"
#include "memory.h"
#include <stdio.h>
#include <EEPROM.h>

volatile unsigned char cmd_type[MAX_COMMAND_BUF] = {CMD_NA}; // The actual commands
volatile unsigned char cmd_count = 0;                        // Conunt of how many commands are in the buffer
volatile unsigned char cmd_pos;                              // Record the current command being handled

extern void audio_callback(float **in, float **out, size_t size);

void command_init()
{
    //------------------------INT disabled
    noInterrupts();
    for (int i = 0; i < MAX_COMMAND_BUF; i++)
    {
        cmd_type[i] = CMD_NA;
    }
    cmd_count = 0;
    cmd_pos = 0;
    interrupts();
    //------------------------INT enabled
}

// The command handler
int command_handler()
{
    //------------------------INT disabled
    noInterrupts();
    if (cmd_count == 0)
    {
        interrupts();
        return 0;
    }
    unsigned char cmd_type_cpy = cmd_type[cmd_pos];
    cmd_pos++;
    cmd_pos %= MAX_COMMAND_BUF;
    cmd_count--;
    interrupts();
    //------------------------INT enabled

    switch (cmd_type_cpy)
    {
    case CMD_NA:
        break;

    case CMD_EFFECTS_PARAM_INC: // can be better
        if (signal_chain[main_window_ins.cur_effect]->param[effect_param_window_ins.cur_param].enable)
        {
            if (signal_chain[main_window_ins.cur_effect]->param[effect_param_window_ins.cur_param].value + effect_param_window_ins.cur_step <= 255)
            {
                signal_chain[main_window_ins.cur_effect]->param[effect_param_window_ins.cur_param].value += effect_param_window_ins.cur_step;
            }
            else
            {
                signal_chain[main_window_ins.cur_effect]->param[effect_param_window_ins.cur_param].value = 255;
            }
            signal_chain[main_window_ins.cur_effect]->set_param(effect_param_window_ins.cur_param,
                                                                signal_chain[main_window_ins.cur_effect]->param[effect_param_window_ins.cur_param].value);
        }
        break;

    case CMD_EFFECTS_PARAM_DEC: // can be better
        if (signal_chain[main_window_ins.cur_effect]->param[effect_param_window_ins.cur_param].enable)
        {
            if (signal_chain[main_window_ins.cur_effect]->param[effect_param_window_ins.cur_param].value - effect_param_window_ins.cur_step >= 0)
            {
                signal_chain[main_window_ins.cur_effect]->param[effect_param_window_ins.cur_param].value -= effect_param_window_ins.cur_step;
            }
            else
            {
                signal_chain[main_window_ins.cur_effect]->param[effect_param_window_ins.cur_param].value = 0;
            }
            signal_chain[main_window_ins.cur_effect]->set_param(effect_param_window_ins.cur_param,
                                                                signal_chain[main_window_ins.cur_effect]->param[effect_param_window_ins.cur_param].value);
        }
        break;

    case CMD_UI_SIG_CUR_LEFT:
        if (main_window_ins.cur_effect != 9)
        {
            main_window_ins.cur_effect++;
        }
        break;

    case CMD_UI_SIG_CUR_RIGHT:
        if (main_window_ins.cur_effect != 0)
        {
            main_window_ins.cur_effect--;
        }
        break;

    case CMD_UI_SIG_CUR_SELECT:
        if (signal_chain[main_window_ins.cur_effect] != nullptr)
            display.change_window(EFFECT_PARAM_WINDOW);
        else
            display.change_window(EFFECT_SELECT_WINDOW);
        break;

    case CMD_UI_SIG_CUR_ONOFF:
        if (signal_chain[main_window_ins.cur_effect] != nullptr)
        {
            signal_chain[main_window_ins.cur_effect]->enable = !signal_chain[main_window_ins.cur_effect]->enable;
        }
        break;

    case CMD_UI_SIG_CUR_DEL:
        if (signal_chain[main_window_ins.cur_effect] != nullptr)
        {
            effects_rack.effect_used[signal_chain[main_window_ins.cur_effect]->id] = false;
            signal_chain[main_window_ins.cur_effect] = nullptr;
        }
        break;

    case CMD_UI_SIG_CUR_OPT:
        display.change_window(OPTIONS_WINDOW);
        break;

    case CMD_UI_PARAM_CUR_LEFT:
        if (effect_param_window_ins.cur_param > 1)
        {
            effect_param_window_ins.cur_param -= 2;
        }
        break;

    case CMD_UI_PARAM_CUR_RIGHT:
        if (effect_param_window_ins.cur_param < 4)
        {
            effect_param_window_ins.cur_param += 2;
        }
        break;

    case CMD_UI_PARAM_CUR_UP:
        if (effect_param_window_ins.cur_param % 2 != 0)
        {
            effect_param_window_ins.cur_param--;
        }
        break;

    case CMD_UI_PARAM_CUR_DOWN:
        if (effect_param_window_ins.cur_param % 2 != 1)
        {
            effect_param_window_ins.cur_param++;
        }
        break;

    case CMD_UI_PARAM_CUR_SELECT:
        display.change_window(MAIN_WINDOW);
        break;

    case CMD_UI_PARAM_STEP:
        if (effect_param_window_ins.cur_step == 1)
        {
            effect_param_window_ins.cur_step = 3;
        }
        else if (effect_param_window_ins.cur_step == 3)
        {
            effect_param_window_ins.cur_step = 7;
        }
        else if (effect_param_window_ins.cur_step == 7)
        {
            effect_param_window_ins.cur_step = 1;
        }
        break;

    case CMD_UI_EFFECT_CUR_UP:
        if (effect_select_window_ins.cur_effect_id > 1)
        {
            effect_select_window_ins.cur_effect_id--;
        }
        break;

    case CMD_UI_EFFECT_CUR_DOWN:
        if (effect_select_window_ins.cur_effect_id < EFFECTS_AMOUNT - 1)
        {
            effect_select_window_ins.cur_effect_id++;
        }
        break;

    case CMD_UI_EFFECT_PAGE_UP:
        if (effect_select_window_ins.cur_effect_id - 4 > 0)
        {
            effect_select_window_ins.cur_effect_id -= 4;
        }
        else
        {
            effect_select_window_ins.cur_effect_id = 1;
        }
        
        break;

    case CMD_UI_EFFECT_PAGE_DOWN:
        if (effect_select_window_ins.cur_effect_id + 4 < EFFECTS_AMOUNT)
        {
            effect_select_window_ins.cur_effect_id += 4;
        }
        else
        {
            effect_select_window_ins.cur_effect_id = EFFECTS_AMOUNT - 1;
        }
        break;

    case CMD_UI_EFFECT_CUR_SELECT:
        if (!effects_rack.effect_used[effect_select_window_ins.cur_effect_id])
        {
            signal_chain[main_window_ins.cur_effect] = effects_rack.effects_arr[effect_select_window_ins.cur_effect_id];
            effects_rack.effect_used[effect_select_window_ins.cur_effect_id] = true;
            display.change_window(MAIN_WINDOW);
        }
        break;

    case CMD_UI_EFFECT_CUR_CANCEL:
        display.change_window(MAIN_WINDOW);
        break;

    case CMD_UI_PRESET_UP:
        if (effects_rack.cur_preset > 0)
        {
            effects_rack.change_preset(effects_rack.cur_preset - 1);

        }
        break;

    case CMD_UI_PRESET_DOWN:
        if (effects_rack.cur_preset < MAX_USER_PRESET - 1)
        {
            effects_rack.change_preset(effects_rack.cur_preset + 1);
        }
        break;

    case CMD_UI_OPT_CUR_UP:
        if (options_window_ins.cur_option > 0)
        {
            options_window_ins.cur_option--;
        }
        break;

    case CMD_UI_OPT_CUR_DOWN:
        if (options_window_ins.cur_option < OPTIONS_AMOUNT - 1)
        {
            options_window_ins.cur_option++;
        }

        break;

    case CMD_UI_OPT_PAGE_UP:
        if (options_window_ins.cur_option - 4 >= 0)
        {
            options_window_ins.cur_option -= 4;
        }
        else
        {
            options_window_ins.cur_option = 0;
        }
        
        break;

    case CMD_UI_OPT_PAGE_DOWN:
        if (options_window_ins.cur_option + 4 < OPTIONS_AMOUNT)
        {
            options_window_ins.cur_option += 4;
        }
        else
        {
            options_window_ins.cur_option = OPTIONS_AMOUNT - 1;
        }
        break;

    case CMD_UI_OPT_BACK:
        display.change_window(MAIN_WINDOW);
        break;

    case CMD_OPT_INC:
        switch (options_window_ins.cur_option)
        {
        case OPT_LED_BRIGHTNESS:
            if (options_window_ins.led_lvl < 250)
            {
                options_window_ins.led_lvl += 25;
                u8g2_8x8.setContrast(options_window_ins.led_lvl);
            }
            break;
        
        case OPT_DELAY_UNIT:
            options_window_ins.delay_ms = !options_window_ins.delay_ms;
            effects_rack.effects_arr[DELAY_MOD_ID]->set_param(0, effects_rack.effects_arr[DELAY_MOD_ID]->param[0].value);
            break;

        default:
            break;
        }

        break;

    case CMD_OPT_DEC:
        switch (options_window_ins.cur_option)
        {
        case OPT_LED_BRIGHTNESS:
            if (options_window_ins.led_lvl >= 25)
            {
                options_window_ins.led_lvl -= 25;
                u8g2_8x8.setContrast(options_window_ins.led_lvl);
            }
            break;
        
        case OPT_DELAY_UNIT:
            options_window_ins.delay_ms = !options_window_ins.delay_ms;
            effects_rack.effects_arr[DELAY_MOD_ID]->set_param(0, effects_rack.effects_arr[DELAY_MOD_ID]->param[0].value);
            break;

        default:
            break;
        }

        break;

    case CMD_OPT_SELECT:
        switch (options_window_ins.cur_option)
        {
        case OPT_SAVE_FLASH:
            effects_rack.save_cur_preset_num();
            effects_rack.save_cur_preset();
            options_window_ins.save_options();
            memory.memory_valid = 1;
            
            int bytes_wrote;
            char msg2[20];
            bytes_wrote = memory.save_to_flash();
            itoa(bytes_wrote, msg2, 10);
            show_msg(MSG_INFO, 13, "Save Successful", msg2);

            break;

        default:
            break;
        }

        break;

    default:
        break;
    }
    
    return 1;
}