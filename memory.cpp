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
}

void _memory::init()
{
    read_from_flash();
}

void _memory::read_from_flash()
{
    // TBD
}

void _memory::save_to_flash()
{
    // TBD
}