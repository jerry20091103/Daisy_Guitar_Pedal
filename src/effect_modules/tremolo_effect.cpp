#include "tremolo_effect.h"

void tremolo_effect::init()
{
    // Initialize
    trem.Init(sample_rate);
    // Initialize all parameters
    init_param(0, "Rate", true, 70, FLOAT, 0, "BPM");

    init_param(1, "Depth", true, 128, FLOAT, 2);

    init_param(2, "Wave", true, 125, STRING);

    // Initialize name
    strcpy(effect_short_name, "Trem");
    strcpy(effect_name, "Tremolo");
}

void tremolo_effect::process(float in, float &out)
{
    if (enable)
    {
        out = trem.Process(in);
    }
    else // bypass
    {
        out = in;
    }
}

void tremolo_effect::set_param(uint8_t id, unsigned char val)
{
    param[id].value = val;
    switch (id)
    {
    case 0:
        param[id].true_val.fp = 30 + val; // 30 ~ 285 bpm
        trem.SetFreq(param[id].true_val.fp / 60);
        break;

    case 1:
        param[id].true_val.fp = float(val) * 0.0039; // 0 ~ 1
        trem.SetDepth(param[id].true_val.fp);
        break;
    
    case 2:
        switch (val % 5)
        {
        case 0:
            strcpy(param[id].true_val.str, "SIN");
            trem.SetWaveform(Oscillator::WAVE_SIN);
            break;

        case 1:
            strcpy(param[id].true_val.str, "TRIANGLE");
            trem.SetWaveform(Oscillator::WAVE_POLYBLEP_TRI);
            break;

        case 2:
            strcpy(param[id].true_val.str, "SAWTOOTH");
            trem.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
            break;
        
        case 3:
            strcpy(param[id].true_val.str, "RAMP");
            trem.SetWaveform(Oscillator::WAVE_RAMP);
            break;
        
        case 4:
            strcpy(param[id].true_val.str, "SQUARE");
            trem.SetWaveform(Oscillator::WAVE_POLYBLEP_SQUARE);
            break;
        
        default:
            break;
        }
        break;

    default:
        // Maybe do an error log
        break;
    }
}