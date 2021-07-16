#ifndef TUNER_H
#define TUNER_H

#include "arduinoFFT.h"
#include "src/effect_modules/effects.h"

#define TUNER_SAMPLE_SIZE 2048
#define TUNER_SAMPLE_RATE_DIVIDER 2

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
    unsigned char divider_state;
};

extern _tuner tuner;

#endif 