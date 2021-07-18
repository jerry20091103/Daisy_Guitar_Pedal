#include "gain_effect.h"

void gain_effect::init()
{
    // Initialize
    time_count = 0;
    cur_peak = 0;
    cur_sum = 0;
    // Initialize all parameters
    init_param(0, "Amount", true, 150, FLOAT, 1, "dB");

    init_param(1, "Peak", true, 0, FLOAT, 1, "dB"); // show current peak value (in 0.5 second)

    init_param(2, "RMS", true, 0, FLOAT, 1, "dB"); // show current rms value (in 0.5 second)

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
        param[1].true_val.fp = 20 * daisysp::fastlog10f(cur_peak);
        cur_peak = 0;
        // rms
        cur_sum = daisysp::fmax(cur_sum, 0.000001f);
        param[2].true_val.fp = 20 * daisysp::fastlog10f(daisysp::fastroot(cur_sum/24000, 2));
        cur_sum = 0;
    }
}

void gain_effect::set_param(uint8_t id, unsigned char val)
{
    param[id].value = val;
    switch (id)
    {
    case 0:
        param[id].true_val.fp = -30 + (float)val * 0.2; // -30 ~ 21 dB
        amount = daisysp::pow10f(param[id].true_val.fp * 0.05);
        break;

    default:
        // Maybe do an error log
        break;
    }
}