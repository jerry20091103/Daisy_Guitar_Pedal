#include "effects.h"
#include "reverb_effect.h"

enum effect_id : unsigned char
{
    EMPTY_EFFECT_ID,
    REVERB_MOD01_ID
};

class _effects_rack
{
public:
    void init();
    void read_preset(unsigned char preset);
    void read_cur_preset_num();
    void save_cur_preset_num();
    unsigned char cur_preset;
    reverb_effect reverb_mod01;
};

// A home for all effect instances
extern _effects_rack effects_rack;

// the main signal chain
extern effects *signal_chain[10];
