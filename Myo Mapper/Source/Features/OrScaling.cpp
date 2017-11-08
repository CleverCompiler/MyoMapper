#include "OrScaling.h"

void OrScaling::setValue (float InValue, float InMin, float InMax, float OutMin, float OutMax, int Reverse, float OffSet)
{
    offset = OffSet;
    inValue = InValue;
    inMin = InMin;
    inMax = InMax;
    outMin = OutMin;
    outMax = OutMax;
    reverse = Reverse;
    
    // scale between 0 and 1
    scaled = (inValue + PI) / (2 * PI); // scale input from -PI,PI to 0,1
    
    // limit input
    calibrated = std::max (scaled, inMin); // limit lower values
    calibrated = std::min (scaled, inMax); // limit maximum values
    
    // calibrate
    input1 = 1 - offset;
    calibrated = scaled + input1;
    calibrated = calibrated - 0.5;
    
    // mod
    calibrated = calibrated * 10000000;
    calibrated = (float) ((int)(calibrated) % (int)10000000);
    calibrated = calibrated * 0.0000001;
    
    // reverse value
    calibrated = std::abs(reverse - calibrated);
    
    // scale output
    calibrated = jmap (calibrated, inMin, inMax, outMin, outMax);
}

float OrScaling::getValue()
{
    return calibrated;
}
