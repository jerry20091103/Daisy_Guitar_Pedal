#include "chorus_effect.h"

void chorus_effect::init()
{
    // Initialize
    chorus.Init(sample_rate);
    // Initialize all parameters
    init_param(0, "Rate", true, 22, FLOAT, 2, "Hz");

    init_param(1, "Depth", true, 100, FLOAT, 2);

    init_param(2, "Delay", true, 100, FLOAT, 2, "ms");

    init_param(3, "Feedback", true, 0, FLOAT, 2);

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
        param[id].true_val.fp = 0.1 + float(val) * (float(val) * 0.8 + 51) * 0.0002; // 0.1 ~ 13.11 Hz
        chorus.SetLfoFreq(param[id].true_val.fp);
        break;

    case 1:
        param[id].true_val.fp = float(val) * 0.0039; // 0 ~ 1
        chorus.SetLfoDepth(param[id].true_val.fp);
        break;
    
    case 2:
        param[id].true_val.fp = 0.5 + float(val) * 0.1941; // 0.5 ~ 50 ms
        chorus.SetDelayMs(param[id].true_val.fp);
        break;

    case 3:
        param[id].true_val.fp = float(val) * 0.0039; // 0 ~ 1
        chorus.SetFeedback(param[id].true_val.fp);

    default:
        // Maybe do an error log
        break;
    }
}