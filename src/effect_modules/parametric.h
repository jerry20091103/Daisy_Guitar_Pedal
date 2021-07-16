/* Parametric.h 
    written by @malcolm20 at kvraudio.com
    https://www.kvraudio.com/forum/viewtopic.php?f=33&t=521184
*/
#ifndef Parametric_h
#define Parametric_h

#include <cmath>

#pragma once

class Parametric
{
public:
    typedef enum { LS, HS, PK, NA } ParametricType;

    Parametric(void)
    {
        reset();
        
        q = 0.0f;
        frequency = 0.0f;
        
        this->filterType = NA;
    }
    
    ~Parametric(void) { }
    
    void setFilterType(ParametricType type)
    {
        this->filterType = type;
    }
    
    void reset()
    {
        gain = 0.0f;
        
        xL1 = xL2 = 0.0f;
        yL1 = yL2 = 0.0f;
        
        b0 = b1 = b2 = 0.0f;
        a0 = a1 = a2 = 0.0f;
    }
    
    float Filter(float xL)
    {
        float yL0 = (b0*xL + b1*xL1 + b2*xL2 - a1*yL1 - a2*yL2);
        
        xL2 = xL1;
        xL1 = xL;
        
        yL2 = yL1;
        yL1 = yL0;
        
        return yL0;
    }
    
    void CalcCoeffs(float gain, float frequency, float q = 0.7071)
    {
        this->q = q;
        this->gain = gain;
        this->frequency = frequency;
        
        float A     = powf(10.0f, (gain / 40.0f));
        float omega = 2.0f * M_PI * frequency / 44100.0f;
        float tsin  = sinf(omega);
        float tcos  = cosf(omega);
        float beta  = sqrtf(A+A);
        float alpha = 0.0f;
        
        switch(this->filterType)
        {
            case LS:
                
                a0 = (A+1.0)+(A-1.0)*tcos+beta*tsin;
                a1 = (-2.0*((A-1.0)+(A+1.0)*tcos)) / a0;
                a2 = ((A+1.0)+(A-1.0)*tcos-beta*tsin) / a0;
                
                b0 = (A*((A+1.0)-(A-1.0)*tcos+beta*tsin)) / a0;
                b1 = (2.0*A*((A-1.0)-(A+1.0)*tcos)) / a0;
                b2 = (A*((A+1.0)-(A-1.0)*tcos-beta*tsin)) / a0;
                
                break;
                
            case HS:

                a0 = (A+1.0)-(A-1.0)*tcos+beta*tsin;
                a1 = (2.0*((A-1.0)-(A+1.0)*tcos)) / a0;
                a2 = ((A+1.0)-(A-1.0)*tcos-beta*tsin) / a0;
                
                b0 = (A*((A+1.0)+(A-1.0)*tcos+beta*tsin)) / a0;
                b1 = (-2.0*A*((A-1.0)+(A+1.0)*tcos)) / a0;
                b2 = (A*((A+1.0)+(A-1.0)*tcos-beta*tsin)) / a0;
                
                break;
                
            case PK:
                
                alpha = tsin / (2.0f * q);
                
                a0 = (1.0f + alpha/A);
                a1 = (-2.0f * tcos) / a0;
                a2 = (1.0f - alpha/A) / a0;
                
                b0 = (1.0f + alpha*A) / a0;
                b1 = (-2.0f * tcos) / a0;
                b2 = (1.0f - alpha*A) / a0;
                
                break;
                
            case NA:
                reset();
                break;
                
            default:
                reset();
                break;
        }
    }
    
    float q;
    float gain;
    float frequency;
    
    ParametricType filterType;
    
private:
    float b0, b1, b2;
    float a0, a1, a2;
    
    float xL1, xL2;
    float yL1, yL2;
};

#endif /* Parametric_h */
