#ifndef EQUALIZER_EFFECT_H
#define EQUALIZER_EFFECT_H

#include "effects.h"
#include "parametric.h"

// a six band graphic EQ
// each band is approx. 6/5 octaves apart.
class equalizer_effect : public effects
{
public:
    virtual void process(float in, float &out) override;
    virtual void set_param(uint8_t id, unsigned char val) override;
    virtual void init() override;

private:
    const float q_value = 1.17;

    const float pk_80_freq = 80;
    const float pk_184_freq = 184;
    const float pk_422_freq = 422;
    const float pk_970_freq = 970;
    const float pk_2230_freq = 2230;
    const float pk_5120_freq = 5210;

    Parametric pk_80 = Parametric();
    Parametric pk_184 = Parametric();
    Parametric pk_422 = Parametric();
    Parametric pk_970 = Parametric();
    Parametric pk_2230 = Parametric();
    Parametric pk_5120 = Parametric();
};

#endif