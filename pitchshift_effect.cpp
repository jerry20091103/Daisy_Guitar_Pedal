#include "pitchshift_effect.h"

void pitchshift_effect::init()
{
    // Initialize
    pitchshift.Init(sample_rate);
    // Initialize all parameters
    strcpy(param[0].name, "Dry");
    param[0].enable = true;
    param[0].value = 250;
    set_param(0, param[0].value);

    strcpy(param[1].name, "Wet");
    param[1].enable = true;
    param[1].value = 200;
    set_param(1, param[1].value);

    strcpy(param[2].name, "Amount");
    param[2].enable = true;
    param[2].value = 127;
    set_param(2, param[2].value);

    strcpy(param[3].name, "Buf Size");
    param[3].enable = true;
    param[3].value = 131;
    set_param(3, param[3].value);

    // Initialize name
    strcpy(effect_short_name, "Pith");
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
        param[0].true_val = (float)val * 0.0039;
        dry = param[0].true_val;
        break;
    case 1:
        param[1].true_val = (float)val * 0.0039;
        wet = param[1].true_val;
        break;
    case 2:
        param[2].true_val = ((float)val - 127) * 0.1;
        pitchshift.SetTransposition(param[2].true_val);
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
        param[3].true_val = target;
        pitchshift.SetDelSize(target);
        break;

    default:
        // Maybe do an error log
        break;
    }
}