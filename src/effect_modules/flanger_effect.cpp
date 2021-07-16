#include "flanger_effect.h"

void flanger_effect::init()
{
    // Initialize
    flang.Init(sample_rate);
    // Initialize all parameters
    init_param(0, "Rate", true, 25);

    init_param(1, "Depth", true, 128);

    init_param(2, "Delay", true, 40);

    init_param(3, "Feedback", true, 120);

    // Initialize name
    strcpy(effect_short_name, "Flng");
    strcpy(effect_name, "Flanger");
}

void flanger_effect::process(float in, float &out)
{
    if (enable)
    {
        out = flang.Process(in);
    }
    else // bypass
    {
        out = in;
    }
}

void flanger_effect::set_param(uint8_t id, unsigned char val)
{
    param[id].value = val;
    switch (id)
    {
    case 0:
        param[id].true_val = 0.1 + float(val) * (float(val) * 0.8 + 51) * 0.00015; // 0.1 ~ 9.85 Hz
        flang.SetLfoFreq(param[id].true_val);
        break;

    case 1:
        param[id].true_val = float(val) * 0.0039; // 0 ~ 1
        flang.SetLfoDepth(param[id].true_val);
        break;
    
    case 2:
        param[id].true_val = 0.1 + float(val) * 0.0232; // 0.1 ~ 6 ms
        flang.SetDelayMs(param[id].true_val);
        break;

    case 3:
        param[id].true_val = float(val) * 0.0039; // 0 ~ 1
        flang.SetFeedback(param[id].true_val);

    default:
        // Maybe do an error log
        break;
    }
}