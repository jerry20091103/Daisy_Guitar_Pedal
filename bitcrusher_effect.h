#ifndef BITCRUSHER_EFFECT_H
#define BITCRUSHER_EFFECT_H

#include "effects.h"

class bitcrusher_effect : public effects
{
public:
    virtual void process(float in, float &out) override;
    virtual void set_param(uint8_t id, unsigned char val) override;
    virtual void init() override;
private:
    daisysp::Bitcrush bitcrush;
    unsigned char sample_mode;
    unsigned char bit_mode;
};

#endif