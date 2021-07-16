#include "IR_filter_effect.h"

IR_filter_effect IR_ins;

void IR_filter_effect::init()
{
    // Initialize
    memory.load_ir(0);
    fir.Init(memory.cur_ir.fp, IR_LENGTH, true);
    // Initialize all parameters
    init_param(0, "Mode", true, 128);

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
        param[id].true_val = val % memory.ir_num;
        memory.load_ir(param[id].true_val);
        fir.SetIR(memory.cur_ir.fp, 256, true);
        break;

    default:
        // Maybe do an error log
        break;
    }
}