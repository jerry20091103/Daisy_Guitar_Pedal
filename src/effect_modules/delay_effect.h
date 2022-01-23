#ifndef DELAY_EFFECT_H
#define DELAY_EFFECT_H

#include "effects.h"

// global delay buffer for 2 seconds
extern daisysp::DelayLine<float, 96000> DSY_SDRAM_BSS delay_buf;

class delay_effect : public effects
{
public:
    virtual void process(float in, float &out) override;
    virtual void set_param(uint8_t id, unsigned char val) override;
    virtual void init() override;
private:
    daisysp::Tone tone;
    float feedback;
    float mix;
    float delay_time;
    bool range;
    bool reverse;
};

#endif