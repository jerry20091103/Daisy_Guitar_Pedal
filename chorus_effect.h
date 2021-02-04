#ifndef CHORUS_EFFECT_H
#define CHORUS_EFFECT_H

#include "effects.h"

class chorus_effect : public effects
{
public:
    virtual void process(float in, float &out) override;
    virtual void set_param(uint8_t id, unsigned char val) override;
    virtual void init() override;
private:
    daisysp::ChorusEngine chorus;
};

#endif