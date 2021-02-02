#include "overdrive_effect.h"

void overdrive_effect::init()
{
    // Initialize
    od.Init();
    // Initialize all parameters
    strcpy(param[0].name, "Drive");
    param[0].enable = true;
    param[0].value = 128;
    set_param(0, param[0].value);

    strcpy(param[1].name, "Level");
    param[1].enable = true;
    param[1].value = 128;
    set_param(1, param[1].value);

    // Initialize name
    strcpy(effect_short_name, "Driv");
}

void overdrive_effect::process(float in, float &out)
{
    if (enable)
    {
        float after;
        after = od.Process(in) * 0.5;
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
        param[0].true_val = (float)val * 0.0039;
        od.SetDrive(param[0].true_val);
        break;

    case 1:
        param[1].true_val = (float)val * 0.0025;
        level = param[1].true_val;
        break;

    default:
        // Maybe do an error log
        break;
    }
}