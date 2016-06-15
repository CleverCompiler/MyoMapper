/*
  ==============================================================================

    OSC.h
    Created: 14 Jun 2016 4:33:38pm
    Author:  Balandino Di Donato

  ==============================================================================
*/

#ifndef OSC_H_INCLUDED
#define OSC_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class OSC    : public Component
{
public:
    OSC();
    ~OSC();
    
    void setSender(String HostAddress, int Port);
    void sendOSC(int id,
                 std::array<int8_t, 8> emgRaw,
                 std::array<float, 8> emgScaled,
                 float mav,
                 Vector3D< float > gyro,
                 Vector3D< float > acceleration,
                 Vector3D< float > orientationRaw,
                 Vector3D< float > orientationScaled,
                 String pose,
                 int poseID);
    void connect();
    void disconnect();

private:
    
    OSCSender sender;
    int oscPort;
    String hostAddress;
    bool enableOSCvalue;
    bool oscConnection;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OSC)
};


#endif  // OSC_H_INCLUDED
