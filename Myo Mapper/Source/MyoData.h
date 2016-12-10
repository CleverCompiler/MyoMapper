#ifndef MYODATA_H_INCLUDED
#define MYODATA_H_INCLUDED

#include <array>

struct MyoData
{
    std::array<int8_t, 8> emgRaw;
    std::array<float, 8> emgScaled;
    std::array<float, 8> emgScaledAbs;
    Vector3D< float > gyro;
    Vector3D< float > gyroScaled;
    Vector3D< float > gyroWfL;
    Vector3D< float > gyroScaledWfL;
    Vector3D< float > acceleration;
    Vector3D< float > accelerationScaled;
    Vector3D< float > accelerationWfL;
    Vector3D< float > accelerationScaledWfL;
    Vector3D< float > orientationRaw;
    Vector3D< float > orientationScaled;
    Vector3D< float > orientationScaledWfL;
    String pose;
    int poseID;
    float mav;
    float mavWfL;
};



#endif  // MYODATA_H_INCLUDED
