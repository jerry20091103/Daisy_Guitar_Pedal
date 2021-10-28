#include "cab_effect.h"

cab_effect cab_ins;

void cab_effect::init()
{
    // Initialize parametric filters
    f0.setFilterType(Parametric::LS);
    f1.setFilterType(Parametric::PK);
    f2.setFilterType(Parametric::PK);
    f3.setFilterType(Parametric::PK);
    f4.setFilterType(Parametric::PK);
    f5.setFilterType(Parametric::PK);
    f6.setFilterType(Parametric::HS);

    f0.CalcCoeffs(-24.7, 32.9, 24);
    f1.CalcCoeffs(10.7, 174, 0.35);
    f2.CalcCoeffs(3, 497, 2);
    f3.CalcCoeffs(-0.1, 1330, 0.59);
    f4.CalcCoeffs(11.6, 2606, 1.1);
    f5.CalcCoeffs(-25.5, 8482, 2.5);
    f6.CalcCoeffs(-13, 17351, 24);

    init_param(0, "Mode", true, 128, BOOL);

    // Initialize name
    strcpy(effect_short_name, "Cab ");
    strcpy(effect_name, "Cab Simulator");
}

void cab_effect::process(float in, float &out)
{
    if (enable)
    {
        
        out = f6.Filter(f5.Filter(f4.Filter(f3.Filter(f2.Filter(f1.Filter(f0.Filter(in))))))) * 0.44; // filter and reduce gain (-7dB)
    }
    else // bypass
    {
        out = in;
    }
}

void cab_effect::set_param(uint8_t id, unsigned char val)
{
    param[id].value = val;
    switch (id)
    {
        case 0:
        param[id].true_val.b = val % 2;
        enable = param[id].true_val.b;
        break;

    default:
        // Maybe do an error log
        break;
    }
}