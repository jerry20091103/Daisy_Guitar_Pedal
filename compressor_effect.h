#ifndef COMPRESSOR_EFFECT_H
#define COMPRESSOR_EFFECT_H

#include "effects.h"

class compressor_effect : public effects
{
public:
    virtual void process(float in, float &out) override;
    virtual void set_param(uint8_t id, unsigned char val) override;
    virtual void init() override;
private:
    daisysp::Compressor comp;
    bool view_out;
    bool view_auto;
};

#endif