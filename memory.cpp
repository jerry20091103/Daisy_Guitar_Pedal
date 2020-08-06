#include "memory.h"


_memory memory;

_memory::_memory()
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
    for(int i=0; i<OPTIONS_AMOUNT; i++)
    {
        options_mem[i] = 0;
    }
}

void _memory::init()
{
    read_from_flash();
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
    for(int i=0; i<OPTIONS_AMOUNT; i++)
    {
        options_mem[i] = 0;
    }
}

void _memory::read_from_flash()
{
    // Copy the data from the flash to the buffer
	eeprom_buffer_fill();

    int addr = 0;
    // read memory_valid
    memory_valid = eeprom_buffered_read_byte(addr);
    addr++;
    // read cur_preset_mem
    cur_preset_mem = eeprom_buffered_read_byte(addr);
    addr++;
    // read effect_id_mem
    for (int i = 0; i < MAX_USER_PRESET; i++)
    {
        for (int j = 0; j < MAX_EFFECTS_NUM; j++)
        {
            effect_id_mem[i][j] = eeprom_buffered_read_byte(addr);
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
                effect_param_mem[i][j][k] = eeprom_buffered_read_byte(addr);
                addr++;
            }
        }
    }
    // read effect_enable_mem
    for (int i = 0; i < MAX_USER_PRESET; i++)
    {
        for (int j = 0; j < MAX_EFFECTS_NUM; j++)
        {
            effect_enable_mem[i][j] = eeprom_buffered_read_byte(addr);
            addr++;
        }
    }
    // read options_mem
    for (int i = 0; i < OPTIONS_AMOUNT; i++)
    {
        options_mem[i] = eeprom_buffered_read_byte(addr);
        addr++;
    }
}

int _memory::save_to_flash()
{
    int addr = 0;
    // write valid memory mark = 1
    eeprom_buffered_write_byte(addr, 1);
    addr++;
    // write cur_preset_mem
    eeprom_buffered_write_byte(addr, cur_preset_mem);
    addr++;
    // write effect_id_mem
    for (int i = 0; i < MAX_USER_PRESET; i++)
    {
        for (int j = 0; j < MAX_EFFECTS_NUM; j++)
        {
            eeprom_buffered_write_byte(addr, effect_id_mem[i][j]);
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
                eeprom_buffered_write_byte(addr, effect_param_mem[i][j][k]);
                addr++;
            }
        }
    }
    // write effect_enable_mem
    for (int i = 0; i < MAX_USER_PRESET; i++)
    {
        for (int j = 0; j < MAX_EFFECTS_NUM; j++)
        {
            eeprom_buffered_write_byte(addr, effect_enable_mem[i][j]);
            addr++;
        }
    }
    // write options_mem
    for (int i = 0; i < OPTIONS_AMOUNT; i++)
    {
        eeprom_buffered_write_byte(addr, options_mem[i]);
        addr++;
    }

    // Copy the data from the buffer to the flash
	eeprom_buffer_flush();
    
    return addr;
}