#include "IR_filter_effect.h"

IR_filter_effect IR_ins;

void IR_filter_effect::init()
{
    // Initialize
    memory.load_ir(0);
    fir.Init(memory.cur_ir.fp, IR_LENGTH, true);
    // Initialize all parameters
    strcpy(param[0].name, "Mode");
    param[0].enable = true;
    param[0].value = 128;
    set_param(0, param[0].value);

    // Initialize name
    strcpy(effect_short_name, " IR ");
    strcpy(effect_name, "IR Cab_Sim");
}

void IR_filter_effect::process(float in, float &out)
{
    if (param[0].true_val != 0)
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
        param[0].true_val = val % memory.ir_num;
        memory.load_ir(param[0].true_val);
        fir.SetIR(memory.cur_ir.fp, 256, true);
        break;

    default:
        // Maybe do an error log
        break;
    }
}