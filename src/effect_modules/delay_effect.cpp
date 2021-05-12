#include "delay_effect.h"
#include "src/windows/options_window.h"

daisysp::DelayLine<float, 96000> DSY_SDRAM_BSS delay_buf;

void delay_effect::init()
{
    // Initialize
    delay_buf.Init();
    tone.Init(sample_rate);
    // Initialize all parameters
    strcpy(param[0].name, "Time");
    param[0].enable = true;
    param[0].value = 50;
    set_param(0, param[0].value);

    strcpy(param[1].name, "Feedback"); 
    param[1].enable = true;
    param[1].value = 129;
    set_param(1, param[1].value);

    strcpy(param[2].name, "Mix");
    param[2].enable = true;
    param[2].value = 129;
    set_param(2, param[2].value);

    strcpy(param[3].name, "LP Freq");
    param[3].enable = true;
    param[3].value = 150;
    set_param(3, param[3].value);

    strcpy(param[4].name, "Range"); // two ranges for delay time
    param[4].enable = true;
    param[4].value = 128;
    set_param(4, param[4].value);

    // Initialize name
    strcpy(effect_short_name, "Dely");
    strcpy(effect_name, "Delay");
}

void delay_effect::process(float in, float &out)
{
    if (enable)
    {
        float new_delay, delay_out;
        delay_out = delay_buf.Read();
        new_delay = delay_out * feedback * feedback + in;
        delay_buf.Write(tone.Process(new_delay));

        out = in + delay_out * mix * mix;
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
            param[id].true_val = 30 + val;
        }
        else
        {
            param[id].true_val = 285 + val;
        }
        // convert bpm to ms
        delay_time = (1 / float(param[id].true_val)) * 60000;
        if(options_window_ins.delay_ms)
            param[id].true_val = delay_time;
        delay_buf.SetDelay(delay_time * 48);
        break;

    case 1: // feedback
        param[id].true_val = (float)val * 0.0039;
        feedback = param[id].true_val;
        break;
    
    case 2: // mix
        param[id].true_val = (float)val * 0.0039;
        mix = param[id].true_val;
        break;
    
    case 3: // tone
        param[id].true_val = 400 + val * ((float)val * 0.9 + 25.5) * 0.3;
        tone.SetFreq(param[id].true_val);
        break;

    case 4: // range
        param[id].true_val = val % 2;
        range = (bool)param[id].true_val;
        set_param(0, param[0].value);
        break;

    default:
        // Maybe do an error log
        break;
    }
}