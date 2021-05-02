#include "chorus_effect.h"

void chorus_effect::init()
{
    // Initialize
    chorus.Init(sample_rate);
    // Initialize all parameters
    strcpy(param[0].name, "Rate");
    param[0].enable = true;
    param[0].value = 22;
    set_param(0, param[0].value);

    strcpy(param[1].name, "Depth");
    param[1].enable = true;
    param[1].value = 100;
    set_param(1, param[1].value);

    strcpy(param[2].name, "Delay");
    param[2].enable = true;
    param[2].value = 100;
    set_param(2, param[2].value);

    strcpy(param[3].name, "Feedback");
    param[3].enable = true;
    param[3].value = 0;
    set_param(3, param[3].value);


    // Initialize name
    strcpy(effect_short_name, "Chor");
    strcpy(effect_name, "Chorus");
}

void chorus_effect::process(float in, float &out)
{
    if (enable)
    {
        out = chorus.Process(in);
    }
    else // bypass
    {
        out = in;
    }
}

void chorus_effect::set_param(uint8_t id, unsigned char val)
{
    param[id].value = val;
    switch (id)
    {
    case 0:
        param[0].true_val = 0.1 + float(val) * (float(val) * 0.8 + 51) * 0.0002; // 0.1 ~ 13.11 Hz
        chorus.SetLfoFreq(param[0].true_val);
        break;

    case 1:
        param[1].true_val = float(val) * 0.0039; // 0 ~ 1
        chorus.SetLfoDepth(param[1].true_val);
        break;
    
    case 2:
        param[2].true_val = 0.5 + float(val) * 0.1941; // 0.5 ~ 50 ms
        chorus.SetDelayMs(param[2].true_val);
        break;

    case 3:
        param[3].true_val = float(val) * 0.0039; // 0 ~ 1
        chorus.SetFeedback(param[3].true_val);

    default:
        // Maybe do an error log
        break;
    }
}