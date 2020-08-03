#ifndef MEMORY_H
#define MEMORY_H

#include "effects.h"

#define MAX_USER_PRESET 10

class _memory
{
public:
    _memory();
    void init();
    void save_to_flash();
    void read_from_flash();
    unsigned char cur_preset_mem;
    unsigned char effect_id_mem[MAX_USER_PRESET][MAX_EFFECTS_NUM]; // [preset][effect]
    unsigned char effect_param_mem[MAX_USER_PRESET][MAX_EFFECTS_NUM][MAX_PARAM_NUM]; // [preset][effect][param]
    unsigned char effect_enable_mem[MAX_USER_PRESET][MAX_EFFECTS_NUM]; // [preset][effect]
    unsigned char setting_mem;
};

extern _memory memory;

#endif