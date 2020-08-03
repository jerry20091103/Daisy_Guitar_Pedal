#include "reverb_effect.h"

void reverb_effect::init()
{
    // Initialize reverbsc
    reverb.Init(sample_rate);
    // Initial all the parameters
    strcpy("Feedback", param[0].name);
    param[0].enable = true;
    param[0].value = 180;
    set_param(0, param[0].value);

    strcpy("LP Freq", param[1].name);
    param[1].enable = true;
    param[1].value = 190;
    set_param(1, param[1].value);

    strcpy("Dry", param[2].name);
    param[2].enable = true;
    param[2].value = 200;
    set_param(2, param[2].value);

    strcpy("Wet", param[3].name);
    param[3].enable = false;
    param[3].value = 200;
    set_param(3, param[3].value);

    // Initialize name
    strcpy(effect_short_name, "Revb");
}

void reverb_effect::process(float in, float &out)
{
    if (enable)
    {
        float after_l = 0.0f;
        float after_r = 0.0f;
        reverb.Process(in, in, &after_l, &after_r);
        after_l = after_l * 0.5f + after_r * 0.5f; // Mix two channels
        out = in * dry + after_l * wet;            // Dry and wet mix
    }
    else // bypass
    {
        out = in;
    }
}

void reverb_effect::set_param(uint8_t id, unsigned char val)
{
    float value;
    switch (id)
    {
    case 0:
        value = (float)val * 0.0039;
        reverb.SetFeedback(value);
        break;
    case 1:
        value = 800 + (float)val * 75;
        reverb.SetLpFreq(value);
        break;
    case 2:
        value = (float)val * 0.0039;
        dry = value;
        break;
    case 3:
        value = (float)val * 0.0039;
        wet = value;
        break;
    default:
        // Maybe do an error log
        break;
    }
}