#include "src/tuner.h"
#include "src/effect_modules/effects.h"

_tuner tuner;

void _tuner::init()
{
    tuner_sample_rate = 48000;
    threshold = 0;
    filter_freq = 5000;
    cur_pos = 0;
    for (int i = 0; i < TUNER_SAMPLE_SIZE; i++)
    {
        in_buffer[i] = 0;
    }
}

void _tuner::process(float in)
{
        in_buffer[cur_pos] = f2s16(in);
        cur_pos = (cur_pos + 1) % TUNER_SAMPLE_SIZE;
        // // shift entire buffer and add new sample
        // for (int i = TUNER_SAMPLE_SIZE - 1; i > 0; i--)
        // {
        //     in_buffer[i] = in_buffer[i - 1];
        // }
        // in_buffer[0] = f2s16(in);
}

float _tuner::get_frequency()
{
    int temp_pos = 0;
    sum = 0;
    pd_state = 0;
    int period = 0;
    for (int i = 0; i < TUNER_SAMPLE_SIZE; i++)
    {
        // Autocorrelation
        sum_old = sum;
        sum = 0;
        for (int k = 0; k < TUNER_SAMPLE_SIZE - i; k++)
        {
            temp_pos = (k + cur_pos) % TUNER_SAMPLE_SIZE;
            sum += (in_buffer[temp_pos]) * (in_buffer[temp_pos + i]) / 65536;
        }

        // Peak Detect State Machine
        if (pd_state == 2 && (sum - sum_old) <= 0)
        {
            period = i;
            pd_state = 3;
        }
        if (pd_state == 1 && (sum > thresh) && (sum - sum_old) > 0)
            pd_state = 2;
        if (!i)
        {
            thresh = sum * 0.5;
            pd_state = 1;
        }
    }
    // Frequency identified in Hz
    if (thresh > 100)
    {
        freq_per = tuner_sample_rate / (period-1);
    }
    return freq_per;
}

void _tuner::set_threshold(float val)
{
    threshold = val;
}
