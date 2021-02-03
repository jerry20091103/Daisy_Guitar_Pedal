#ifndef FUZZ_EFFECT_H
#define FUZZ_EFFECT_H

#include "effects.h"

class fuzz_effect : public effects
{
public:
    virtual void process(float in, float &out) override;
    virtual void set_param(uint8_t id, unsigned char val) override;
    virtual void init() override;
private:
    daisysp::Tone tone;
    float gain;
    float threshold;
    float level;
};

#endif