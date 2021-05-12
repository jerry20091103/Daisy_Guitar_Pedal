#ifndef ANALOG_EFFECT_H
#define ANALOG_EFFECT_H

#include "effects.h"

class analog_effect : public effects
{
public:
    virtual void process(float in, float &out) override;
    virtual void set_param(uint8_t id, unsigned char val) override;
    virtual void init() override;
};

#endif