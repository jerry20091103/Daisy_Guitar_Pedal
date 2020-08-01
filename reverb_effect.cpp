#include "reverb_effect.h"

void reverb_effect::init()
{
    // Initialize reverbsc
    reverb.Init(sample_rate);
    // Initial all the parameters
    strcpy("Feedback", param[0].name);
    param[0].enable = true;
    param[0].value = 0.7f;
    set_param(0, param[0].value);

    strcpy("LP Freq", param[1].name);
    param[1].enable = true;
    param[1].value = 15000.0f;
    set_param(1, param[1].value);

    strcpy("Dry", param[2].name);
    param[2].enable = true;
    param[2].value = 0.8f;
    set_param(2, param[2].value);

    strcpy("Wet", param[3].name);
    param[3].enable = false;
    param[3].value = 0.8f;
    set_param(3, param[3].value);
}

void reverb_effect::process(float in, float &out)
{
    float after_l = 0.0f; 
    float after_r = 0.0f;
    reverb.Process(in, in, &after_l, &after_r);
    after_l = after_l * 0.5f + after_r * 0.5f; // Mix two channels
    out = in * dry + after_l * wet;            // Dry and wet mix
}

void reverb_effect::set_param(uint8_t id, float val)
{
    switch (id)
    {
    case 0:
        reverb.SetFeedback(val);
        break;
    case 1:
        reverb.SetLpFreq(val);
        break;
    case 2:
        dry = val;
        break;
    case 3:
        wet = val;
        break;
    default:
        // Maybe do an error log
        break;
    }
}