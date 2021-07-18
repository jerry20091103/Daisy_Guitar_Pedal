#include "reverb_effect.h"

void reverb_effect::init()
{
    // Initialize reverbsc
    reverb.Init(sample_rate);
    // Initialize all parameters
    init_param(0, "Feedback", true, 180, FLOAT, 2);

    init_param(1, "LP Freq", true, 218, FLOAT, 0, "Hz");

    init_param(2, "Dry", true, 200, FLOAT, 2);

    init_param(3, "Wet", true, 200, FLOAT, 2);

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
        out = in * dry + (after_l + after_r) * 0.5 * wet;            // Dry and wet mix
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
        param[id].true_val.fp = (float)val * 0.0039;
        reverb.SetFeedback(fastlog10f(param[id].true_val.fp + 0.112) + 0.953);
        break;
    case 1:
        param[id].true_val.fp =  400 + val * ((float)val * 0.9 + 25.5) * 0.3;
        reverb.SetLpFreq(param[id].true_val.fp);
        break;
    case 2:
        param[id].true_val.fp = (float)val * 0.0039;
        dry = param[id].true_val.fp;
        break;
    case 3:
        param[id].true_val.fp = (float)val * 0.0039;
        wet = param[id].true_val.fp;
        break;
    default:
        // Maybe do an error log
        break;
    }
}