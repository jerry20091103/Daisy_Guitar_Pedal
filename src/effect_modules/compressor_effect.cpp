#include "compressor_effect.h"

void compressor_effect::init()
{
    // Initialize
    comp.Init(sample_rate);
    view_out = false;
    view_auto = false;
    // Initialize all parameters
    init_param(0, "Ratio", true, 91, FLOAT, 2);

    init_param(1, "Thd/Out", true, 100, FLOAT, 1, "dB");

    init_param(2, "Attack", true, 20, FLOAT, 2, "s");

    init_param(3, "Release", true, 75, FLOAT, 2, "s");

    init_param(4, "Makeup", true, 0, FLOAT, 2, "dB");

    init_param(5, "AutoGain", true, 127, BOOL);

    // Initialize name
    strcpy(effect_short_name, "Comp");
    strcpy(effect_name, "Compressor");
}

void compressor_effect::process(float in, float &out)
{
    if (enable)
    {
        out = comp.Process(in);
        param[1].true_val.fp = comp.GetGain(); //show reduction gain
        if(!view_out)
        {
            view_out= true;
        }
    }
    else // bypass
    {
        out = in;
        if(view_out)
        {
            unsigned char val = param[1].value;
            param[1].true_val.fp = -((float)val * ((float)val * 0.8 + 51) * 0.0012);
            view_out = false;
        }
    }
    // update auto makeup value
    if(param[5].true_val.b)
    {
        param[4].true_val.fp = comp.GetMakeup();
        if(!view_auto)
            view_auto = true;
    }
    else
    {
        if(view_auto)
        {
            unsigned char val = param[4].value;
            param[4].true_val.fp = -((float)val * ((float)val * 0.8 + 51) * 0.0012);
            view_auto = false;
        }
    }
    
}

void compressor_effect::set_param(uint8_t id, unsigned char val)
{
    param[id].value = val;
    switch (id)
    {
    case 0: // ratio
        param[id].true_val.fp = 1 + (float)val * ((float)val * 0.8 + 51) * 0.000446; // 1 ~ 30.001 
        comp.SetRatio(param[id].true_val.fp);
        break;

    case 1: // threshold
        param[id].true_val.fp = -((float)val * ((float)val * 0.8 + 51) * 0.0012); // 0 ~ -78.03
        comp.SetThreshold(param[id].true_val.fp);
        break;

    case 2: // attack
        param[id].true_val.fp = 0.001 + (float)val * ((float)val * 0.9 + 25) * 0.00015; // 0.001 ~ 9.74
        comp.SetAttack(param[id].true_val.fp);
        break;

    case 3: // release
        param[id].true_val.fp = 0.001 + (float)val * ((float)val * 0.9 + 25) * 0.00015; // 0.001 ~ 9.74
        comp.SetRelease(param[id].true_val.fp);
        break;
    
    case 4: // makeup
        // if auto makeup
        if(param[5].true_val.b)
        {
            param[id].true_val.fp = comp.GetMakeup();
        }
        // manual makeup
        else
        {
            param[id].true_val.fp = ((float)val * ((float)val * 0.8 + 51) * 0.0012); // 0 ~ 78.03
            comp.SetMakeup(param[id].true_val.fp);
        }
        break;
    
    case 5: // auto makeup
        param[id].true_val.b = val%2;
        comp.AutoMakeup(param[id].true_val.b);
        break;

    default:
        // Maybe do an error log
        break;
    }
}