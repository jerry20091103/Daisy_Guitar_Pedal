#include "effects.h"
#include "reverb_effect.h"
#include "analog_effect.h"
#include "pitchshift_effect.h"
#include "gain_effect.h"
#include "overdrive_effect.h"
#include "fuzz_effect.h"
#include "compressor_effect.h"
#include "delay_effect.h"

#define EFFECTS_AMOUNT 9 // How many effects

enum effect_id : unsigned char
{
    EMPTY_EFFECT_ID,
    REVERB_MOD01_ID,
    ANALOG_ID,
    PITCHSHIFT_MOD01_ID,
    OVERDRIVE_MOD01_ID,
    FUZZ_MOD01_ID,
    COMPRESSOR_MOD01_ID,
    GAIN_MOD01_ID,
    DELAY_MOD_ID
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
private:
    // All effect instances
    reverb_effect reverb_mod01;
    analog_effect analog;
    pitchshift_effect pitchshift_mod01;
    overdrive_effect overdrive_mod01;
    fuzz_effect fuzz_mod01;
    compressor_effect compressor_mod01;
    gain_effect gain_mod01;
    delay_effect delay_mod;
};

// A home for all effect instances
extern _effects_rack effects_rack;

// the main signal chain
extern effects *signal_chain[MAX_EFFECTS_NUM];
