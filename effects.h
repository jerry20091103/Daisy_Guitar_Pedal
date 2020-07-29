#ifndef EFFECTS_H
#define EFFECTS_H

#include <DaisyDuino.h>
#include <string.h>
#define MAX_EFFECTS_NUM 10 // A max of 10 effects for now
#define MAX_PARAM_NAME 10 // A name of an parameter can only be 9 characters max
#define MAX_PARAM_NUM 4 // Only 4 parameters max

struct effects_param
{
    char name[MAX_PARAM_NAME]; 
    float value; // Stores the value of parameter
    bool enable; // whether the parameter is enabled or not
};

// A virtual class for inheritance
class effects
{
public:
    // Process the effect
    virtual void process(float in, float &out) = 0;
    // Set the param["id"] to "val"
    virtual void set_param(uint8_t id, float val) = 0;
    // Initialize the effect
    virtual void init() = 0;
    effects();

protected:
    effects_param param[MAX_PARAM_NUM];
};
// A global variable to store sample rate
extern float sample_rate;

#endif