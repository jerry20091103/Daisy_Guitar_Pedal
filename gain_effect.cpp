#include "gain_effect.h"

void gain_effect::init()
{
    // Initialize
    time_count = 0;
    cur_peak = 0;
    cur_sum = 0;
    // Initialize all parameters
    strcpy(param[0].name, "Amount");
    param[0].enable = true;
    param[0].value = 150;
    set_param(0, param[0].value);

    strcpy(param[1].name, "Peak"); // show current peak value (in 0.5 second)
    param[1].enable = true;
    param[1].value = 0;
    set_param(1, param[1].value);

    strcpy(param[2].name, "RMS"); // show current rms value (in 0.5 second)
    param[2].enable = true;
    param[2].value = 0;
    set_param(2, param[2].value);


    // Initialize name
    strcpy(effect_short_name, "Gain");
    strcpy(effect_name, "Gain");
}

void gain_effect::process(float in, float &out)
{
    if (enable)
    {
        out = in * amount;     
    }
    else // bypass
    {
        out = in;
    }
    // show peak and rms
    float amp = fabs(out);
    time_count++;
    cur_peak = daisysp::fmax(cur_peak, amp);
    cur_sum += amp*amp;
    if(time_count >= 24000)
    {
        time_count = 0;
        // peak
        cur_peak = daisysp::fmax(cur_peak, 0.000001f);
        param[1].true_val = 20 * daisysp::fastlog10f(cur_peak);
        cur_peak = 0;
        // rms
        cur_sum = daisysp::fmax(cur_sum, 0.000001f);
        param[2].true_val = 20 * daisysp::fastlog10f(daisysp::fastroot(cur_sum/24000, 2));
        cur_sum = 0;
    }
}

void gain_effect::set_param(uint8_t id, unsigned char val)
{
    param[id].value = val;
    switch (id)
    {
    case 0:
        param[id].true_val = -30 + (float)val * 0.2; // -30 ~ 21 dB
        amount = daisysp::pow10f(param[id].true_val * 0.05);
        break;

    default:
        // Maybe do an error log
        break;
    }
}