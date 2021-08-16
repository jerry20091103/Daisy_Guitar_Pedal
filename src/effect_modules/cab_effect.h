#ifndef CAB_EFFECT_H
#define CAB_EFFECT_H

#include "effects.h"
#include "parametric.h"

// a cab sim with EQ
class cab_effect : public effects
{
public:
    virtual void process(float in, float &out) override;
    virtual void set_param(uint8_t id, unsigned char val) override;
    virtual void init() override;

private:
    Parametric f0 = Parametric();
    Parametric f1 = Parametric();
    Parametric f2 = Parametric();
    Parametric f3 = Parametric();
    Parametric f4 = Parametric();
    Parametric f5 = Parametric();
    Parametric f6 = Parametric();
};

#endif