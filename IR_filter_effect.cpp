#include "IR_filter_effect.h"

void IR_filter_effect::init()
{
    // Initialize
    fir.Init(ir_01, 512, true);
    // Initialize all parameters
    
    
    
    

    // Initialize name
    strcpy(effect_short_name, " IR ");
    strcpy(effect_name, "IR Cab_Sim");
}

void IR_filter_effect::process(float in, float &out)
{
    if (enable)
    {
        out = fir.Process(in);
    }
    else // bypass
    {
        out = in;
    }
}

void IR_filter_effect::set_param(uint8_t id, unsigned char val)
{
    param[id].value = val;
    switch (id)
    {
    case 0:
        
        break;

    default:
        // Maybe do an error log
        break;
    }
}