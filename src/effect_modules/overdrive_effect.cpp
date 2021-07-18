#include "overdrive_effect.h"

void overdrive_effect::init()
{
    // Initialize
    od.Init();
    tone.Init(sample_rate);
    // Initialize all parameters
    init_param(0, "Drive", true, 128, FLOAT, 2);

    init_param(1, "Level", true, 128, FLOAT, 2);

    init_param(2, "LP Freq", true, 127, FLOAT, 0, "Hz");

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
        out = after * level;       
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
        param[id].true_val.fp = (float)val * 0.0039;
        od.SetDrive(param[id].true_val.fp);
        break;

    case 1:
        param[id].true_val.fp = (float)val * 0.0039;
        level = param[id].true_val.fp * param[id].true_val.fp;
        break;

    case 2:
        param[id].true_val.fp = 400 + val * ((float)val * 0.9 + 25.5) * 0.2;
        tone.SetFreq(param[id].true_val.fp);
        break;

    default:
        // Maybe do an error log
        break;
    }
}