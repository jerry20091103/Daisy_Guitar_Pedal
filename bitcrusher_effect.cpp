#include "bitcrusher_effect.h"

void bitcrusher_effect::init()
{
    // Initialize
    bitcrush.Init(sample_rate);
    // Initialize all parameters
    strcpy(param[0].name, "Rate");
    param[0].enable = true;
    param[0].value = 120;
    set_param(0, param[0].value);

    strcpy(param[1].name, "Bit");
    param[1].enable = true;
    param[1].value = 127;
    set_param(1, param[1].value);

    // Initialize name
    strcpy(effect_short_name, "Bit ");
    strcpy(effect_name, "Bitcrusher");
}

void bitcrusher_effect::process(float in, float &out)
{
    if (enable)
    {
        out = bitcrush.Process(in);
    }
    else // bypass
    {
        out = in;
    }
}

void bitcrusher_effect::set_param(uint8_t id, unsigned char val)
{
    param[id].value = val;
    switch (id)
    {
    case 0:
        sample_mode = val % 10 ; // 0.1 ~ 9.85 Hz
        switch (sample_mode)
        {
        case 0:
            param[0].true_val = 48000;
            break;
        case 1:
            param[0].true_val = 32000;
            break;
        case 2:
            param[0].true_val = 24000;
            break; 
        case 3:
            param[0].true_val = 16000;
            break; 
        case 4:
            param[0].true_val = 12000;
            break;
        case 5:
            param[0].true_val = 9600;
            break; 
        case 6:
            param[0].true_val = 8000;
            break; 
        case 7:
            param[0].true_val = 6000;
            break; 
        case 8:
            param[0].true_val = 4800;
            break; 
        case 9:
            param[0].true_val = 2400;
            break; 

        default:
            param[0].true_val = 48000;
            break; 
        }
        bitcrush.SetCrushRate(param[0].true_val);
        break;

    case 1:
        param[1].true_val = val % 16 + 1; // 1 ~ 16
        bitcrush.SetBitDepth((int)param[1].true_val);
        break;

    default:
        // Maybe do an error log
        break;
    }
}