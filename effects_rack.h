#include "effects.h"
#include "reverb_effect.h"

class _effects_rack
{
public:
    void init();
    reverb_effect reverb_mod01;
};

// A home for all effect instances
_effects_rack effects_rack;

// the main signal chain
effects *signal_chain[10] = {nullptr};

// Initialize all effect instances
void _effects_rack::init()
{
    reverb_mod01.init();
    strcpy(reverb_mod01.effect_name, "Reverb1");
}
