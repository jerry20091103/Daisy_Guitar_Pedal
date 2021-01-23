#include "effects_rack.h"
#include "memory.h"

// A home for all effect instances
_effects_rack effects_rack;

// the main signal chain
effects *signal_chain[MAX_EFFECTS_NUM] = {nullptr};

// Initialize all effect instances
void _effects_rack::init()
{
    // reset signal_chain
    for(int i=0; i<MAX_EFFECTS_NUM; i++)
        signal_chain[i] = nullptr;
    // Init effects
    reverb_mod01.init();
    analog.init();
    // Set effect id
    reverb_mod01.id = REVERB_MOD01_ID;
    analog.id = ANALOG_ID;
    // Set effect names
    strcpy(reverb_mod01.effect_name, "Reverb1");
    strcpy(analog.effect_name, "Analog");
    // Assign to effect_arr
    effects_arr[EMPTY_EFFECT_ID] = nullptr;
    effects_arr[REVERB_MOD01_ID] = &reverb_mod01;
    effects_arr[ANALOG_ID] = &analog;
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

        // if not empty effect
        if (signal_chain[i] != nullptr)
        {
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
}

void _effects_rack::save_cur_preset()
{
    for (unsigned char i = 0; i < MAX_EFFECTS_NUM; i++)
    {
        // if null
        if (signal_chain[i] == nullptr)
        {
            memory.effect_id_mem[cur_preset][i] = 0;
            for (unsigned char j = 0; j < MAX_PARAM_NUM; j++)
            {
                memory.effect_param_mem[cur_preset][i][j] = 0;
            }
            memory.effect_enable_mem[cur_preset][i] = 0;
        }
        else
        {
            // save effect id
            memory.effect_id_mem[cur_preset][i] = signal_chain[i]->id;

            // save effect parameters
            for (unsigned char j = 0; j < MAX_PARAM_NUM; j++)
            {
                memory.effect_param_mem[cur_preset][i][j] = signal_chain[i]->param[j].value;
            }

            // save effect enable
            if (signal_chain[i]->enable)
            {
                memory.effect_enable_mem[cur_preset][i] = 1;
            }
            else
            {
                memory.effect_enable_mem[cur_preset][i] = 0;
            }
        }
    }
}

void _effects_rack::change_preset(unsigned char preset)
{
    save_cur_preset();
    read_preset(preset);
    cur_preset = preset;
}

void _effects_rack::read_cur_preset_num()
{
    cur_preset = memory.cur_preset_mem;
}

void _effects_rack::save_cur_preset_num()
{
    memory.cur_preset_mem = cur_preset;
}