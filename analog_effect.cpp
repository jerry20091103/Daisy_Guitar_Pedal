#include "analog_effect.h"
#include "display.h"

void analog_effect::init()
{
    // Initial all the parameters
    strcpy(param[0].name, "Multi-OD");
    param[0].enable = true;
    param[0].value = 100;
    set_param(0, param[0].value);

    strcpy(param[1].name, "Dist.");
    param[1].enable = true;
    param[1].value = 100;
    set_param(1, param[1].value);

    strcpy(param[2].name, "Tube");
    param[2].enable = true;
    param[2].value = 100;
    set_param(2, param[2].value);


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
        param[id].true_val = val % 2;
        mcp.digitalWrite(RELAY_0_PIN, param[id].true_val); // control the relay
        break;
    case 1:
        param[id].true_val = val % 2;
        mcp.digitalWrite(RELAY_1_PIN, param[id].true_val);
        break;
    case 2:
        param[id].true_val = val % 2;
        mcp.digitalWrite(RELAY_2_PIN, param[id].true_val);
        break;
    default:
        // Maybe do an error log
        break;
    }
}
