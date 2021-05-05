#ifndef MEMORY_H
#define MEMORY_H

#include "effects.h"
#include "options_window.h"
#include <Wire.h>
#include "extEEPROM.h"

#define MAX_USER_PRESET 10
#define IR_LENGTH 512

typedef union{
    float fp[IR_LENGTH];
    byte bin[IR_LENGTH * 4];
} binary_float;

// Strores user preserts, options and IRs
// Handle load / save with external EEPROM
class _memory
{
public:
    _memory();
    void init();
    int save_to_flash();
    void read_from_flash();
    void reset_memory();
    void reset_flash();
    void read_ir_num();
    int load_ir(uint8_t id);
    unsigned char memory_valid;
    unsigned char cur_preset_mem;
    unsigned char effect_id_mem[MAX_USER_PRESET][MAX_EFFECTS_NUM]; // [preset][effect]
    unsigned char effect_param_mem[MAX_USER_PRESET][MAX_EFFECTS_NUM][MAX_PARAM_NUM]; // [preset][effect][param]
    unsigned char effect_enable_mem[MAX_USER_PRESET][MAX_EFFECTS_NUM]; // [preset][effect]
    unsigned char options_mem[OPTIONS_AMOUNT];
    binary_float cur_ir;
    unsigned char ir_num;
};



extern _memory memory;
extern extEEPROM eep;

#endif