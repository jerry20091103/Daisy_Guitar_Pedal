#ifndef GAIN_EFFECT_H
#define GAIN_EFFECT_H

#include "effects.h"

class gain_effect : public effects
{
public:
    virtual void process(float in, float &out) override;
    virtual void set_param(uint8_t id, unsigned char val) override;
    virtual void init() override;
private:
    float amount;
};

#endif