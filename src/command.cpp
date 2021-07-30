#include "command.h"
#include "display.h"
#include "src/windows/main_window.h"
#include "src/windows/effect_param_window.h"
#include "src/windows/effect_select_window.h"
#include "src/windows/msg_window.h"
#include "src/windows/options_window.h"
#include "src/effect_modules/effects_rack.h"
#include "src/looper.h"
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

// put a new command into the queue
void insert_command(command cmd)
{
    cmd_type[(cmd_pos + cmd_count) % MAX_COMMAND_BUF] = cmd;
    cmd_count++;
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
    cmd_type[cmd_pos] = CMD_NA;
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
            uint8_t cur_value = signal_chain[main_window_ins.cur_effect]->param[effect_param_window_ins.cur_param].value;
            if (cur_value + effect_param_window_ins.cur_step <= 255)
            {
                cur_value += effect_param_window_ins.cur_step;
            }
            else
            {
                cur_value = 255;
            }
            signal_chain[main_window_ins.cur_effect]->set_param(effect_param_window_ins.cur_param, cur_value);
        }
        break;

    case CMD_EFFECTS_PARAM_DEC: // can be better
        if (signal_chain[main_window_ins.cur_effect]->param[effect_param_window_ins.cur_param].enable)
        {
            uint8_t cur_value = signal_chain[main_window_ins.cur_effect]->param[effect_param_window_ins.cur_param].value;
            if (cur_value - effect_param_window_ins.cur_step >= 0)
            {
                cur_value -= effect_param_window_ins.cur_step;
            }
            else
            {
                cur_value = 0;
            }
            signal_chain[main_window_ins.cur_effect]->set_param(effect_param_window_ins.cur_param, cur_value);
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
    
    case CMD_UI_SIG_SWAP_UP:
        if(main_window_ins.cur_effect != 0)
        {
            effects* temp = signal_chain[main_window_ins.cur_effect];
            signal_chain[main_window_ins.cur_effect] = signal_chain[main_window_ins.cur_effect-1];
            main_window_ins.cur_effect--;
            signal_chain[main_window_ins.cur_effect] = temp;
        }
        break;
    
    case CMD_UI_SIG_SWAP_DOWN:
        if(main_window_ins.cur_effect != MAX_EFFECTS_NUM-1)
        {
            effects* temp = signal_chain[main_window_ins.cur_effect];
            signal_chain[main_window_ins.cur_effect] = signal_chain[main_window_ins.cur_effect+1];
            main_window_ins.cur_effect++;
            signal_chain[main_window_ins.cur_effect] = temp;
        }
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

    case CMD_UI_PRESET_SWAP_UP:
        if(effects_rack.cur_preset != 0)
        {
            effects_rack.save_cur_preset();
            effects_rack.swap_preset(effects_rack.cur_preset, effects_rack.cur_preset - 1);
            effects_rack.cur_preset--;
            effects_rack.read_preset(effects_rack.cur_preset);
        }
        break;
    
    case CMD_UI_PRESET_SWAP_DOWN:
        if(effects_rack.cur_preset != MAX_USER_PRESET - 1)
        {
            effects_rack.save_cur_preset();
            effects_rack.swap_preset(effects_rack.cur_preset, effects_rack.cur_preset + 1);
            effects_rack.cur_preset++;
            effects_rack.read_preset(effects_rack.cur_preset);
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

        case OPT_IR:
            IR_ins.set_param(0, IR_ins.param[0].value + 1);
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
        
        case OPT_IR:
            IR_ins.set_param(0, IR_ins.param[0].value - 1);
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
            looper.save_options();
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
    
    case CMD_LOOPER_RECORD:
        if(display.current_window->get_window_id() != LOOPER_WINDOW)
            display.change_window(LOOPER_WINDOW);
        looper.record();
        break;
    
    case CMD_LOOPER_STOP:
        if(display.current_window->get_window_id() != LOOPER_WINDOW)
            display.change_window(LOOPER_WINDOW);
        looper.stop();
        break;
    
    case CMD_LOOPER_REDO:
        looper.redo();
        break;
    
    case CMD_LOOPER_UNDO:
        looper.undo();
        break;
    
    case CMD_LOOPER_BACK:
        display.change_window(MAIN_WINDOW);
        break;
    
    case CMD_LOOPER_LVL_INC:
        looper.loop_level_inc();
        break;
    
    case CMD_LOOPER_LVL_DEC:
        looper.loop_level_dec();
        break;
    
    case CMD_LOOPER_POS_INC:
        looper.loop_pos_inc();
        break;
    
    case CMD_LOOPER_POS_DEC:
        looper.loop_pos_dec();
        break;
    
    case CMD_LOOPER_POS_START:
        looper.set_loop_pos(0);
        break;
    
    case CMD_OPEN_TUNER:
        display.change_window(TUNER_WINDOW);

    default:
        break;
    }
    
    return 1;
}