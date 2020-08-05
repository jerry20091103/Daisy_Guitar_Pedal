#ifndef EFFECTS_H
#define EFFECTS_H

#include <DaisyDuino.h>
#include <string.h>

#define MAX_EFFECTS_NUM 10 // A max of 10 effects for now
#define MAX_PARAM_NAME 9 // A name of an parameter can only be 8 characters max
#define MAX_PARAM_NUM 6 // Only 6 parameters max
#define MAX_EFFECT_NAME 20
#define MAX_EFFECT_SHORT_NAME 5

struct effects_param
{
    char name[MAX_PARAM_NAME]; 
    float true_val; // The parameter's converted value
    unsigned char value; // Stores the value of parameter
    bool enable; // whether the parameter is enabled or not
};

// A virtual class for inheritance
class effects
{
public:
    // Process the effect
    virtual void process(float in, float &out) = 0;
    // Set the param["id"] to "val"
    virtual void set_param(uint8_t id, unsigned char val) = 0;
    // Initialize the effect
    virtual void init() = 0;
    effects();
    char effect_name[MAX_EFFECT_NAME];
    char effect_short_name[MAX_EFFECT_SHORT_NAME];
    bool enable = false;
    effects_param param[MAX_PARAM_NUM];
    unsigned char id;

protected:
};
// A global variable to store sample rate
extern float sample_rate;

#endif