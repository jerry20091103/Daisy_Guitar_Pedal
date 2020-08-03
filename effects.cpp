#include "effects.h"

effects::effects()
{
    // All parameters are not enabled by default
    for (uint8_t i = 0; i < MAX_PARAM_NUM; i++)
    {
        param[i].enable = false;
    }
    // effects are bypassed by default
    enable = false;
}

// A global variable to store sample rate
float sample_rate;