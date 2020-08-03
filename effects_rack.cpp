#include "effects_rack.h"
#include "memory.h"

// A home for all effect instances
_effects_rack effects_rack;

// the main signal chain
effects *signal_chain[10] = {nullptr};

// Initialize all effect instances
void _effects_rack::init()
{
    reverb_mod01.init();
    strcpy(reverb_mod01.effect_name, "Reverb1");
}

// Read a preset into the signal_chain
void _effects_rack::read_preset(unsigned char preset)
{
    for (unsigned char i = 0; i < MAX_EFFECTS_NUM; i++)
    {
        // read effect id
        switch (memory.effect_id_mem[preset][i])
        {
        case EMPTY_EFFECT_ID:
            signal_chain[i] = nullptr;
            break;
        case REVERB_MOD01_ID:
            signal_chain[i] = &reverb_mod01;
            break;
        
        default:
            signal_chain[i] = nullptr;
            break;
        }

        // read effect parameters
        for(unsigned char j=0; j<MAX_PARAM_NUM; j++)
        {
            signal_chain[i]->set_param(j, memory.effect_param_mem[preset][i][j]);
        }

        // read effect enable
        if(memory.effect_enable_mem[preset][i])
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