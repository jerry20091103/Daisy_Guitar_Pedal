#include "effects_rack.h"
#include "memory.h"

// A home for all effect instances
_effects_rack effects_rack;

// the main signal chain
effects *signal_chain[10] = {nullptr};

// Initialize all effect instances
void _effects_rack::init()
{
    // Init effects
    reverb_mod01.init();
    // Set effect id
    reverb_mod01.id = REVERB_MOD01_ID;
    // Set effect names
    strcpy(reverb_mod01.effect_name, "Reverb1");
    // Assign to effect_arr
    effects_arr[REVERB_MOD01_ID] = &reverb_mod01;
}

// Read a preset into the signal_chain
void _effects_rack::read_preset(unsigned char preset)
{
    // Set all effects to unused by default
    for (unsigned char i = 0; i < EFFECTS_AMOUNT; i++)
    {
        effect_used[i] = false;
    }
    for (unsigned char i = 0; i < MAX_EFFECTS_NUM; i++)
    {
        // read effect id
        signal_chain[i] = effects_arr[memory.effect_id_mem[preset][i]];
        // Set used status
        effect_used[memory.effect_id_mem[preset][i]] = true;

        // read effect parameters
        for (unsigned char j = 0; j < MAX_PARAM_NUM; j++)
        {
            signal_chain[i]->set_param(j, memory.effect_param_mem[preset][i][j]);
        }

        // read effect enable
        if (memory.effect_enable_mem[preset][i])
        {
            signal_chain[i]->enable = true;
        }
        else
        {
            signal_chain[i]->enable = false;
        }
    }
}

void _effects_rack::read_cur_preset_num()
{
    cur_preset = memory.cur_preset_mem;
}

void _effects_rack::save_cur_preset_num()
{
    memory.cur_preset_mem = cur_preset;
}

char* _effects_rack::get_effect_name(unsigned char id)
{
    switch (id)
    {
    case REVERB_MOD01_ID:
        return reverb_mod01.effect_name;
        break;

    default:
        return 0;
        break;
    }
}