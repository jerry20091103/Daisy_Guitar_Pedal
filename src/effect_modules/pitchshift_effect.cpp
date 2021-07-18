#include "pitchshift_effect.h"

void pitchshift_effect::init()
{
    // Initialize
    pitchshift.Init(sample_rate);
    // Initialize all parameters
    init_param(0, "Dry", true, 250, FLOAT, 2);

    init_param(1, "Wet", true, 200, FLOAT, 2);

    init_param(2, "Amount", true, 127, FLOAT, 1);

    init_param(3, "Buf Size", true, 131, FLOAT, 0);

    // Initialize name
    strcpy(effect_short_name, "Pith");
    strcpy(effect_name, "Pitch_Shifter");
}

void pitchshift_effect::process(float in, float &out)
{
    if (enable)
    {
        float before = in;
        float after = 0.0f;
        after = pitchshift.Process(before);
        out = in * dry + after * wet;            // Dry and wet mix
    }
    else // bypass
    {
        out = in;
    }
}

void pitchshift_effect::set_param(uint8_t id, unsigned char val)
{
    param[id].value = val;
    int target = 8192;
    switch (id)
    {
    case 0:
        param[id].true_val.fp = (float)val * 0.0039;
        dry = param[id].true_val.fp;
        break;
    case 1:
        param[id].true_val.fp = (float)val * 0.0039;
        wet = param[id].true_val.fp;
        break;
    case 2:
        param[id].true_val.fp = ((float)val - 127) * 0.1;
        pitchshift.SetTransposition(param[id].true_val.fp);
        break;
    case 3:
        switch (val%8)
        {
        case 0:
            target = 1024;
            break;
        case 1:
            target = 1200;
            break;
        case 2: 
            target = 1600;
            break;
        case 3:
            target = 2000;
            break;
        case 4:
            target = 2400;
            break;
        case 5:
            target = 3200;
            break;
        case 6:
            target = 4800;
            break;
        case 7:
            target = 8192;
            break;
        default:
            target = 8192;
            break;
        }
        param[id].true_val.fp = target;
        pitchshift.SetDelSize(target);
        break;

    default:
        // Maybe do an error log
        break;
    }
}