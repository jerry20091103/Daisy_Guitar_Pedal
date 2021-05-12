#ifndef OVERDRIVE_EFFECT_H
#define OVERDRIVE_EFFECT_H

#include "effects.h"

class overdrive_effect : public effects
{
public:
    virtual void process(float in, float &out) override;
    virtual void set_param(uint8_t id, unsigned char val) override;
    virtual void init() override;
private:
    daisysp::Overdrive od;
    daisysp::Tone tone;
    float level;
};

#endif