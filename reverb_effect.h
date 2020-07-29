#ifndef REVERB_EFFECT_H
#define REVERB_EFFECT_H

#include "effects.h"

class reverb_effect : public effects
{
public:
    virtual void process(float in, float &out) override;
    virtual void set_param(uint8_t id, float val) override;
    virtual void init() override;
private:
    daisysp::ReverbSc reverb;
    float dry, wet;
    float time;
};

#endif