#include "analog_effect.h"
#include "src/display.h"

void analog_effect::init()
{
    // Initial all the parameters
    init_param(0, "Multi-OD", true, 100, BOOL);

    init_param(1, "Dist.", true, 100, BOOL);

    init_param(2, "Tube", true, 100, BOOL);

    // Initialize name
    strcpy(effect_short_name, "Anlg");
    strcpy(effect_name, "Analog");
}

void analog_effect::process(float in, float &out)
{
    // Nothing to do here
}

void analog_effect::set_param(uint8_t id, unsigned char val)
{
    param[id].value = val;
    switch (id)
    {
    case 0:
        param[id].true_val.b = val % 2;
        mcp.digitalWrite(RELAY_0_PIN, param[id].true_val.b); // control the relay
        break;
    case 1:
        param[id].true_val.b = val % 2;
        mcp.digitalWrite(RELAY_1_PIN, param[id].true_val.b);
        break;
    case 2:
        param[id].true_val.b = val % 2;
        mcp.digitalWrite(RELAY_2_PIN, param[id].true_val.b);
        break;
    default:
        // Maybe do an error log
        break;
    }
}
