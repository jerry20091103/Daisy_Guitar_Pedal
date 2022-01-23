#include "delay_effect.h"
#include "src/windows/options_window.h"
#include "effects_rack.h"

daisysp::DelayLine<float, 96000> DSY_SDRAM_BSS delay_buf;

void delay_effect::init()
{
    // Initialize
    delay_buf.Init();
    tone.Init(sample_rate);
    // Initialize all parameters
    init_param(0, "Time", true, 50, FLOAT, 0, "BPM");

    init_param(1, "Feedback", true, 129, FLOAT, 2);

    init_param(2, "Mix", true, 129, FLOAT, 2);

    init_param(3, "LP Freq", true, 150, FLOAT, 0, "Hz");

    init_param(4, "Range", true, 128, STRING); // two ranges for delay time

    init_param(5, "Reverse", true, 128, BOOL); // reverse or not

    // Initialize name
    strcpy(effect_short_name, "Dely");
    strcpy(effect_name, "Delay");
}

void delay_effect::process(float in, float &out)
{
    effects_rack.delay_used = true; // mark that delay is used in this callback
    if (enable)
    {
        float new_delay, delay_out;
        delay_out = delay_buf.Read();
        new_delay = delay_out * feedback + in;
        delay_buf.Write(tone.Process(new_delay));

        if(reverse)
            delay_out = delay_buf.ReadReversed();

        out = in + delay_out * mix;
    }
    else // bypass
    {
        out = in;
    }
}

void delay_effect::set_param(uint8_t id, unsigned char val)
{
    param[id].value = val;
    switch (id)
    {
    case 0: // delay time
        if(!range)
        {
            param[id].true_val.fp = 30 + val;
        }
        else
        {
            param[id].true_val.fp = 285 + val;
        }
        // convert bpm to ms
        delay_time = (1 / float(param[id].true_val.fp)) * 60000;
        if(options_window_ins.delay_ms)
        {
            param[id].true_val.fp = delay_time;
            param[id].prec = 2;
            strcpy(param[id].unit, "");
        }
        else
        {
            param[id].prec = 0;
            strcpy(param[id].unit, "BPM");
        }
        
        delay_buf.SetDelay(delay_time * 48);
        break;

    case 1: // feedback
        param[id].true_val.fp = (float)val * 0.0039;
        feedback = param[id].true_val.fp * param[id].true_val.fp;
        break;
    
    case 2: // mix
        param[id].true_val.fp = (float)val * 0.0039;
        mix = param[id].true_val.fp * param[id].true_val.fp;
        break;
    
    case 3: // tone
        param[id].true_val.fp = 400 + val * ((float)val * 0.9 + 25.5) * 0.3;
        tone.SetFreq(param[id].true_val.fp);
        break;

    case 4: // range
        range = (bool)(val % 2);
        strcpy(param[id].true_val.str, range ? "HIGH" : "LOW");
        set_param(0, param[0].value);
        break;

    case 5: // Reverse
        param[id].true_val.b = val % 2;
        reverse = param[id].true_val.b;
        break;

    default:
        // Maybe do an error log
        break;
    }
}