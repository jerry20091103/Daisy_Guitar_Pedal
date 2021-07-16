#ifndef COMMAND_H
#define COMMAND_H

#define MAX_COMMAND_BUF 20

// volatile command variables for interrupt handling

// List of command to commuitcate with main loop
enum command : unsigned char{
    // Empty command
    CMD_NA,
    // Effects command
    CMD_EFFECTS_PARAM_INC,
    CMD_EFFECTS_PARAM_DEC,
    // UI command
    CMD_UI_SIG_CUR_LEFT,
    CMD_UI_SIG_CUR_RIGHT,
    CMD_UI_SIG_CUR_SELECT,
    CMD_UI_SIG_CUR_ONOFF,
    CMD_UI_SIG_CUR_DEL,
    CMD_UI_SIG_CUR_OPT,
    CMD_UI_PARAM_CUR_LEFT,
    CMD_UI_PARAM_CUR_RIGHT,
    CMD_UI_PARAM_CUR_UP,
    CMD_UI_PARAM_CUR_DOWN,
    CMD_UI_PARAM_CUR_SELECT,
    CMD_UI_PARAM_STEP,
    CMD_UI_EFFECT_CUR_UP,
    CMD_UI_EFFECT_CUR_DOWN,
    CMD_UI_EFFECT_PAGE_UP,
    CMD_UI_EFFECT_PAGE_DOWN,
    CMD_UI_EFFECT_CUR_SELECT,
    CMD_UI_EFFECT_CUR_CANCEL,
    CMD_UI_PRESET_UP,
    CMD_UI_PRESET_DOWN,
    CMD_UI_OPT_CUR_UP,
    CMD_UI_OPT_CUR_DOWN,
    CMD_UI_OPT_PAGE_UP,
    CMD_UI_OPT_PAGE_DOWN,
    CMD_UI_OPT_BACK,
    // Options command
    CMD_OPT_INC,
    CMD_OPT_DEC,
    CMD_OPT_SELECT,
    // Looper command
    CMD_LOOPER_RECORD,
    CMD_LOOPER_STOP,
    CMD_LOOPER_UNDO,
    CMD_LOOPER_REDO,
    CMD_LOOPER_BACK,
    CMD_LOOPER_LVL_INC,
    CMD_LOOPER_LVL_DEC,
    // Tuner command
    CMD_OPEN_TUNER,
};

int command_handler();
void command_init();
void insert_command(command cmd);

extern volatile unsigned char cmd_type[MAX_COMMAND_BUF]; // The actuall commands
extern volatile unsigned char cmd_count; // Conunt of how many commands are in the buffer
extern volatile unsigned char cmd_pos; // Record the current command being handled

#endif