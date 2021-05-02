#include "fuzz_effect.h"

void fuzz_effect::init()
{
    // Initialize
    tone.Init(sample_rate);
    // Initialize all parameters
    strcpy(param[0].name, "Gain");
    param[0].enable = true;
    param[0].value = 128;
    set_param(0, param[0].value);

    strcpy(param[1].name, "Level");
    param[1].enable = true;
    param[1].value = 128;
    set_param(1, param[1].value);

    strcpy(param[2].name, "Peak");
    param[2].enable = true;
    param[2].value = 128;
    set_param(2, param[2].value);

    strcpy(param[3].name, "LP Freq");
    param[3].enable = true;
    param[3].value = 128;
    set_param(3, param[3].value);

    // Initialize name
    strcpy(effect_short_name, "Fuzz");
    strcpy(effect_name, "D_Fuzz");
}

void fuzz_effect::process(float in, float &out)
{
    if (enable)
    {
        float fuzzed, after;
        in = in * (1+gain) * (1+gain);
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
        out = after * level*level;       
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
        param[0].true_val = (float)val * 0.06;
        gain = param[0].true_val;
        break;

    case 1:
        param[1].true_val = (float)val * 0.0039;
        level = param[1].true_val;
        break;
    
    case 2:
        param[2].true_val = (float)val * 0.0039;
        threshold = param[2].true_val * 0.5;
        break;

    case 3:
        param[3].true_val = 400 + val * ((float)val * 0.9 + 25.5) * 0.2;
        tone.SetFreq(param[3].true_val);
        break;

    default:
        // Maybe do an error log
        break;
    }
}