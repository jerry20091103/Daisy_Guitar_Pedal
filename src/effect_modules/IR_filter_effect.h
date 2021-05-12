#ifndef IR_FILTER_EFFECT_H
#define IR_FILTER_EFFECT_H

#include "effects.h"
#include "src/memory.h"

class IR_filter_effect : public effects
{
public:
    virtual void process(float in, float &out) override;
    virtual void set_param(uint8_t id, unsigned char val) override;
    virtual void init() override;

private:
    daisysp::FIR<IR_LENGTH, 1> fir;
};

extern IR_filter_effect IR_ins;

#endif