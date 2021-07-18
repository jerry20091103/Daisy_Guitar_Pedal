#ifndef TREMOLO_EFFECT_H
#define TREMOLO_EFFECT_H

#include "effects.h"

class tremolo_effect : public effects
{
public:
    virtual void process(float in, float &out) override;
    virtual void set_param(uint8_t id, unsigned char val) override;
    virtual void init() override;
private:
    daisysp::Tremolo trem;
};

#endif