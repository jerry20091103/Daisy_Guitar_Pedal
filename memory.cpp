#include "memory.h"

_memory memory;

extEEPROM eep(kbits_256, 1, 64); // 24C256 external I2C eeprom

_memory::_memory()
{
    reset_memory();
}

void _memory::init()
{
    if (eep.begin(extEEPROM::twiClock400kHz))
    { //Serial.println("EEPROM error");
        return;
    }
    //Serial.println("EEPROM begin");
}

void _memory::reset_memory()
{
    // set all memory to zero
    for (int i = 0; i < MAX_USER_PRESET; i++)
    {
        for (int j = 0; j < MAX_EFFECTS_NUM; j++)
        {
            for (int k = 0; k < MAX_PARAM_NUM; k++)
            {
                effect_param_mem[i][j][k] = 0;
            }
            effect_id_mem[i][j] = 0;
            effect_enable_mem[i][j] = 0;
        }
    }
    cur_preset_mem = 0;
    memory_valid = 0;
    for (int i = 0; i < OPTIONS_AMOUNT; i++)
    {
        options_mem[i] = 0;
    }
    for (int i = 0; i < IR_LENGTH; i++)
    {
        cur_ir.fp[i] = 0;
    }
}

void _memory::read_from_flash()
{
    int addr = 0;
    // read memory_valid
    memory_valid = eep.read(addr);
    addr++;
    // read options_mem
    for (int i = 0; i < OPTIONS_AMOUNT; i++)
    {
        options_mem[i] = eep.read(addr);
        addr++;
    }
    // read cur_preset_mem
    cur_preset_mem = eep.read(addr);
    addr++;
    // read effect_id_mem
    for (int i = 0; i < MAX_USER_PRESET; i++)
    {
        for (int j = 0; j < MAX_EFFECTS_NUM; j++)
        {
            effect_id_mem[i][j] = eep.read(addr);
            addr++;
        }
    }
    // read effect_param_mem
    for (int i = 0; i < MAX_USER_PRESET; i++)
    {
        for (int j = 0; j < MAX_EFFECTS_NUM; j++)
        {
            for (int k = 0; k < MAX_PARAM_NUM; k++)
            {
                effect_param_mem[i][j][k] = eep.read(addr);
                addr++;
            }
        }
    }
    // read effect_enable_mem
    for (int i = 0; i < MAX_USER_PRESET; i++)
    {
        for (int j = 0; j < MAX_EFFECTS_NUM; j++)
        {
            effect_enable_mem[i][j] = eep.read(addr);
            addr++;
        }
    }
    // read ir_num
    read_ir_num();
}

int _memory::save_to_flash()
{
    int addr = 0;
    // write valid memory mark = 1
    eep.write(addr, memory_valid);
    addr++;
    // write options_mem
    for (int i = 0; i < OPTIONS_AMOUNT; i++)
    {
        eep.write(addr, options_mem[i]);
        addr++;
    }
    // write cur_preset_mem
    eep.write(addr, cur_preset_mem);
    addr++;
    // write effect_id_mem
    for (int i = 0; i < MAX_USER_PRESET; i++)
    {
        for (int j = 0; j < MAX_EFFECTS_NUM; j++)
        {
            eep.write(addr, effect_id_mem[i][j]);
            addr++;
        }
    }
    // write effect_param_mem
    for (int i = 0; i < MAX_USER_PRESET; i++)
    {
        for (int j = 0; j < MAX_EFFECTS_NUM; j++)
        {
            for (int k = 0; k < MAX_PARAM_NUM; k++)
            {
                eep.write(addr, effect_param_mem[i][j][k]);
                addr++;
            }
        }
    }
    // write effect_enable_mem
    for (int i = 0; i < MAX_USER_PRESET; i++)
    {
        for (int j = 0; j < MAX_EFFECTS_NUM; j++)
        {
            eep.write(addr, effect_enable_mem[i][j]);
            addr++;
        }
    }

    return addr;
}

void _memory::read_ir_num()
{
    ir_num = eep.read(1023); // number of irs stored addr[1023]
}

int _memory::load_ir(uint8_t id)
{
    if(id > ir_num)
        return 1;

    int addr = 1024 + IR_LENGTH * 4 * id; // IRs stored after addr[1023]
    for (int i = 0; i < IR_LENGTH; i++)
    {
        for(uint8_t k = 0; k < 4; k++)
        {
            cur_ir.bin[i * 4 + k] = eep.read(addr);
            addr++;
        }
    }
    return 0;
}