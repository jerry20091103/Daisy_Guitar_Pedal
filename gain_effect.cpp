#include "gain_effect.h"

void gain_effect::init()
{
    // Initialize
    amount = 0;
    // Initialize all parameters
    strcpy(param[0].name, "Amount");
    param[0].enable = true;
    param[0].value = 50;
    set_param(0, param[0].value);

    // Initialize name
    strcpy(effect_short_name, "Gain");
}

void gain_effect::process(float in, float &out)
{
    if (enable)
    {
        out = in * ((float)1 + amount);       
    }
    else // bypass
    {
        out = in;
    }
}

void gain_effect::set_param(uint8_t id, unsigned char val)
{
    param[id].value = val;
    switch (id)
    {
    case 0:
        param[0].true_val = ((float)val - 50) * 0.02;
        amount = param[0].true_val;
        break;

    default:
        // Maybe do an error log
        break;
    }
}