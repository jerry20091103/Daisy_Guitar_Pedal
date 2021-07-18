#include "equalizer_effect.h"

void equalizer_effect::init()
{
    // Initialize parametric filters
    pk_80.setFilterType(Parametric::PK);
    pk_184.setFilterType(Parametric::PK);
    pk_422.setFilterType(Parametric::PK);
    pk_970.setFilterType(Parametric::PK);
    pk_2230.setFilterType(Parametric::PK);
    pk_5120.setFilterType(Parametric::PK);

    pk_80.CalcCoeffs(0, pk_80_freq, q_value);
    pk_184.CalcCoeffs(0, pk_184_freq, q_value);
    pk_422.CalcCoeffs(0, pk_422_freq, q_value);
    pk_970.CalcCoeffs(0, pk_970_freq, q_value);
    pk_2230.CalcCoeffs(0, pk_2230_freq, q_value);
    pk_5120.CalcCoeffs(0, pk_5120_freq, q_value);

    // Initialize all parameters
    init_param(0, "80 Hz", true, 130, FLOAT, 1, "dB");
    init_param(2, "184 Hz", true, 130, FLOAT, 1, "dB");
    init_param(4, "422 Hz", true, 130, FLOAT, 1, "dB");
    init_param(1, "970 Hz", true, 130, FLOAT, 1, "dB");
    init_param(3, "2.23 kHz", true, 130, FLOAT, 1, "dB");
    init_param(5, "5.12 kHz", true, 130, FLOAT, 1, "dB");

    // Initialize name
    strcpy(effect_short_name, " EQ ");
    strcpy(effect_name, "Equalizer");
}

void equalizer_effect::process(float in, float &out)
{
    if (enable)
    {
        in *= 0.16667;
        out = pk_80.Filter(in) + pk_184.Filter(in) + pk_422.Filter(in) + pk_970.Filter(in) + pk_2230.Filter(in) + pk_5120.Filter(in);
    }
    else // bypass
    {
        out = in;
    }
}

void equalizer_effect::set_param(uint8_t id, unsigned char val)
{
    param[id].value = val;
    switch (id)
    {
    case 0: // 100Hz
        param[id].true_val.fp = -52 + (float)val * 0.4; // -52 ~ 50 dB
        pk_80.CalcCoeffs(param[id].true_val.fp, pk_80_freq, q_value);
        break;

    case 1: // 800Hz
        param[id].true_val.fp = -52 + (float)val * 0.4; // -52 ~ 50 dB
        pk_970.CalcCoeffs(param[id].true_val.fp, pk_970_freq, q_value);
        break;

    case 2: // 200Hz
        param[id].true_val.fp = -52 + (float)val * 0.4; // -52 ~ 50 dB
        pk_184.CalcCoeffs(param[id].true_val.fp, pk_184_freq, q_value);
        break;

    case 3: // 1.6kHz
        param[id].true_val.fp = -52 + (float)val * 0.4; // -52 ~ 50 dB
        pk_2230.CalcCoeffs(param[id].true_val.fp, pk_2230_freq, q_value);
        break;

    case 4: // 400Hz
        param[id].true_val.fp = -52 + (float)val * 0.4; // -52 ~ 50 dB
        pk_422.CalcCoeffs(param[id].true_val.fp, pk_422_freq, q_value);
        break;

    case 5: // 3.2kHz
        param[id].true_val.fp = -52 + (float)val * 0.4; // -52 ~ 50 dB
        pk_5120.CalcCoeffs(param[id].true_val.fp, pk_5120_freq, q_value);
        break;

    default:
        // Maybe do an error log
        break;
    }
}