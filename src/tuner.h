#ifndef TUNER_H
#define TUNER_H

#include "src/effect_modules/effects.h"

#define TUNER_SAMPLE_SIZE 4096

// FFT based guitar tuner
// GUIs are in tuner_window.h / .cpp
class _tuner
{
public:
    void init();
    void process(float in); // feed sample to detect frequency
    float get_frequency();  // get result frequency
    void set_threshold(float val); // sets the threshold for the tuner to be active
private:
    float tuner_sample_rate;
    int16_t in_buffer[TUNER_SAMPLE_SIZE];
    float threshold;
    int sum, sum_old;
    int thresh = 0;
    float freq_per = 0;
    byte pd_state = 0;
    float filter_freq;
    int cur_pos;
};

extern _tuner tuner;

#endif 