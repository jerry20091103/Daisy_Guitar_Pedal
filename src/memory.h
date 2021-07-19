#ifndef MEMORY_H
#define MEMORY_H

#include "src/effect_modules/effects.h"
#include "src/windows/options_window.h"
#include <Wire.h>
#include "extEEPROM.h"
#include "src/looper.h"

#define MAX_USER_PRESET 10
#define IR_LENGTH 1024

typedef union{
    float fp[IR_LENGTH];
    byte bin[IR_LENGTH * 4];
} binary_float;

struct effect_preset
{
    unsigned char param[MAX_EFFECTS_NUM][MAX_PARAM_NUM];
    unsigned char id[MAX_EFFECTS_NUM];
    unsigned char enable[MAX_EFFECTS_NUM];
};

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
    effect_preset effect_preset_mem[MAX_USER_PRESET];
    unsigned char options_mem[OPTIONS_AMOUNT];
    unsigned char looper_options_mem[LOOPER_OPTIONS_AMOUNT];
    binary_float cur_ir;
    unsigned char ir_num;
};



extern _memory memory;
extern extEEPROM eep;

#endif