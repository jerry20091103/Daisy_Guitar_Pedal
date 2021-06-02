#include "reverb_effect.h"

void reverb_effect::init()
{
    // Initialize reverbsc
    reverb.Init(sample_rate);
    // Initialize all parameters
    strcpy(param[0].name, "Feedback");
    param[0].enable = true;
    param[0].value = 180;
    set_param(0, param[0].value);

    strcpy(param[1].name, "LP Freq");
    param[1].enable = true;
    param[1].value = 218;
    set_param(1, param[1].value);

    strcpy(param[2].name, "Dry");
    param[2].enable = true;
    param[2].value = 200;
    set_param(2, param[2].value);

    strcpy(param[3].name, "Wet");
    param[3].enable = true;
    param[3].value = 200;
    set_param(3, param[3].value);

    // Initialize name
    strcpy(effect_short_name, "Revb");
    strcpy(effect_name, "Reverb");
}

void reverb_effect::process(float in, float &out)
{
    if (enable)
    {
        float after_l = 0.0f;
        float after_r = 0.0f;
        reverb.Process(in, in, &after_l, &after_r);
        out = in * dry + after_l * wet;            // Dry and wet mix
    }
    else // bypass
    {
        out = in;
    }
}

void reverb_effect::set_param(uint8_t id, unsigned char val)
{
    param[id].value = val;
    switch (id)
    {
    case 0:
        param[id].true_val = (float)val * 0.0039;
        reverb.SetFeedback(param[id].true_val);
        break;
    case 1:
        param[id].true_val =  400 + val * ((float)val * 0.9 + 25.5) * 0.3;
        reverb.SetLpFreq(param[id].true_val);
        break;
    case 2:
        param[id].true_val = (float)val * 0.0039;
        dry = param[id].true_val;
        break;
    case 3:
        param[id].true_val = (float)val * 0.0039;
        wet = param[id].true_val;
        break;
    default:
        // Maybe do an error log
        break;
    }
}