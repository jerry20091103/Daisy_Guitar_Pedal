#include "effects.h"
#include "reverb_effect.h"
#include "analog_effect.h"

#define EFFECTS_AMOUNT 3 // How many effects

enum effect_id : unsigned char
{
    EMPTY_EFFECT_ID,
    REVERB_MOD01_ID,
    ANALOG_ID
};

class _effects_rack
{
public:
    void init();
    void read_preset(unsigned char preset);
    void save_cur_preset();
    void read_cur_preset_num();
    void save_cur_preset_num();
    void change_preset(unsigned char preset);
    unsigned char cur_preset = 0;
    bool effect_used[EFFECTS_AMOUNT] = {false};
    effects *effects_arr[EFFECTS_AMOUNT] = {nullptr};
    // All effect instances
    reverb_effect reverb_mod01;
    analog_effect analog;
};

// A home for all effect instances
extern _effects_rack effects_rack;

// the main signal chain
extern effects *signal_chain[10];
