#include "overdrive_effect.h"

void overdrive_effect::init()
{
    // Initialize
    od.Init();
    tone.Init(sample_rate);
    // Initialize all parameters
    strcpy(param[0].name, "Drive");
    param[0].enable = true;
    param[0].value = 128;
    set_param(0, param[0].value);

    strcpy(param[1].name, "Level");
    param[1].enable = true;
    param[1].value = 128;
    set_param(1, param[1].value);

    strcpy(param[2].name, "LP Freq");
    param[2].enable = true;
    param[2].value = 127;
    set_param(2, param[2].value);

    // Initialize name
    strcpy(effect_short_name, "Driv");
    strcpy(effect_name, "D_Overdrive");
}

void overdrive_effect::process(float in, float &out)
{
    if (enable)
    {
        float driven, after;
        driven = od.Process(in) * 0.4;
        after = tone.Process(driven);
        out = after * level*level;       
    }
    else // bypass
    {
        out = in;
    }
}

void overdrive_effect::set_param(uint8_t id, unsigned char val)
{
    param[id].value = val;
    switch (id)
    {
    case 0:
        param[id].true_val = (float)val * 0.0039;
        od.SetDrive(param[id].true_val);
        break;

    case 1:
        param[id].true_val = (float)val * 0.0039;
        level = param[id].true_val;
        break;

    case 2:
        param[id].true_val = 400 + val * ((float)val * 0.9 + 25.5) * 0.2;
        tone.SetFreq(param[id].true_val);
        break;

    default:
        // Maybe do an error log
        break;
    }
}