#include "fuzz_effect.h"

void fuzz_effect::init()
{
    // Initialize
    tone.Init(sample_rate);
    // Initialize all parameters

    init_param(0, "Gain", true, 128, FLOAT, 2);

    init_param(1, "Level", true, 128, FLOAT, 2);

    init_param(2, "Peak", true, 128, FLOAT, 2);

    init_param(3, "LP Freq", true, 128, FLOAT, 0, "Hz");

    // Initialize name
    strcpy(effect_short_name, "Fuzz");
    strcpy(effect_name, "D_Fuzz");
}

void fuzz_effect::process(float in, float &out)
{
    if (enable)
    {
        float fuzzed, after;
        in = in * gain;
        // hard clipping
        if(in > threshold)
        {
            fuzzed = threshold;
        }
        else if (in < -threshold)
        {
            fuzzed = - threshold;
        }
        else
        {
            fuzzed = in;
        }
        after = tone.Process(fuzzed) * 0.5;
        out = after * level;       
    }
    else // bypass
    {
        out = in;
    }
}

void fuzz_effect::set_param(uint8_t id, unsigned char val)
{
    param[id].value = val;
    switch (id)
    {
    case 0:
        param[id].true_val.fp = (float)val * 0.06;
        gain = (1 + param[id].true_val.fp) * (1 + param[id].true_val.fp);
        break;

    case 1:
        param[id].true_val.fp = (float)val * 0.0039;
        level = param[id].true_val.fp * param[id].true_val.fp;
        break;
    
    case 2:
        param[id].true_val.fp = (float)val * 0.0039;
        threshold = param[id].true_val.fp * 0.5;
        break;

    case 3:
        param[id].true_val.fp = 400 + val * ((float)val * 0.9 + 25.5) * 0.2;
        tone.SetFreq(param[id].true_val.fp);
        break;

    default:
        // Maybe do an error log
        break;
    }
}