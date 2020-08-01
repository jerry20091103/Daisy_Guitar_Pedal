#include "command.h"
#include "display.h"
#include "main_window.h"

volatile unsigned char cmd_type[MAX_COMMAND_BUF] = {CMD_NA}; // The actuall commands
volatile unsigned char cmd_count = 0;                        // Conunt of how many commands are in the buffer
volatile unsigned char cmd_pos;                              // Record the current command being handled

void command_handler()
{
    //------------------------INT disabled
    noInterrupts();
    if (cmd_count == 0)
    {
        interrupts();
        return;
    }
    unsigned char cmd_type_cpy = cmd_type[cmd_pos];
    cmd_pos++;
    cmd_pos %= 20;
    cmd_count--;
    interrupts();
    //------------------------INT enabled
    
    switch (cmd_type_cpy)
    {
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

    default:
        break;
    }
}