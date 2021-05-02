#include "compressor_effect.h"

void compressor_effect::init()
{
    // Initialize
    comp.Init(sample_rate);
    view_out = false;
    view_auto = false;
    // Initialize all parameters
    strcpy(param[0].name, "Ratio");
    param[0].enable = true;
    param[0].value = 91;
    set_param(0, param[0].value);

    strcpy(param[1].name, "Thd/Out");
    param[1].enable = true;
    param[1].value = 100;
    set_param(1, param[1].value);

    strcpy(param[2].name, "Attack");
    param[2].enable = true;
    param[2].value = 20;
    set_param(2, param[2].value);

    strcpy(param[3].name, "Release");
    param[3].enable = true;
    param[3].value = 75;
    set_param(3, param[3].value);

    strcpy(param[4].name, "Makeup");
    param[4].enable = true;
    param[4].value = 0;
    set_param(4, param[4].value);

    strcpy(param[5].name, "AutoGain");
    param[5].enable = true;
    param[5].value = 127;
    set_param(5, param[5].value);

    // Initialize name
    strcpy(effect_short_name, "Comp");
    strcpy(effect_name, "Compressor");
}

void compressor_effect::process(float in, float &out)
{
    if (enable)
    {
        out = comp.Process(in);
        param[1].true_val = comp.GetGain(); //show reduction gain
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
            param[1].true_val = -((float)val * ((float)val * 0.8 + 51) * 0.0012);
            view_out = false;
        }
    }
    // update auto makeup value
    if(param[5].true_val)
    {
        param[4].true_val = comp.GetMakeup();
        if(!view_auto)
            view_auto = true;
    }
    else
    {
        if(view_auto)
        {
            unsigned char val = param[4].value;
            param[4].true_val = -((float)val * ((float)val * 0.8 + 51) * 0.0012);
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
        param[0].true_val = 1 + (float)val * ((float)val * 0.8 + 51) * 0.000446; // 1 ~ 30.001 
        comp.SetRatio(param[0].true_val);
        break;

    case 1: // threshold
        param[1].true_val = -((float)val * ((float)val * 0.8 + 51) * 0.0012); // 0 ~ -78.03
        comp.SetThreshold(param[1].true_val);
        break;

    case 2: // attack
        param[2].true_val = 0.001 + (float)val * ((float)val * 0.9 + 25) * 0.00015; // 0.001 ~ 9.74
        comp.SetAttack(param[2].true_val);
        break;

    case 3: // release
        param[3].true_val = 0.001 + (float)val * ((float)val * 0.9 + 25) * 0.00015; // 0.001 ~ 9.74
        comp.SetRelease(param[3].true_val);
        break;
    
    case 4: // makeup
        // if auto makeup
        if(param[5].true_val)
        {
            param[4].true_val = comp.GetMakeup();
        }
        // manual makeup
        else
        {
            param[4].true_val = ((float)val * ((float)val * 0.8 + 51) * 0.0012); // 0 ~ 78.03
            comp.SetMakeup(param[4].true_val);
        }
        break;
    
    case 5: // auto makeup
        param[5].true_val = val%2;
        comp.AutoMakeup(param[5].true_val);
        break;

    default:
        // Maybe do an error log
        break;
    }
}