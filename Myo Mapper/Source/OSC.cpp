#include "../JuceLibraryCode/JuceHeader.h"
#include "OSC.h"
#include "MyoData.h"

OSC::OSC()
:   vibrate (false),
    vibrationType ("null"),
    rescaleMinTest (false),
    rescaleMIN (0),
    rescaleMaxTest (false),
    rescaleMAX (0),
    oscPortSender (5432),
    oscPortReceiver (5431),
    hostAddress ("127.0.0.1"),
    oscConnectionSender (false),
    oscConnectionReceiver (false),
    Id ("0"),
    myoDataIn {"/yaw", "/pitch", "/roll", "/mav"},
    action {"/vibrate", "/centre", "/setMin", "/setMax", "/reverse"}
{
    for (int i = 1; i < 5; ++i) // id
    {
        String I = String(i);
        
        receiver.addListener (this, "/myo" + I + action[0]);
        
        for (int y = 0; y < 4; ++y) // myo data
        {
            for (int z = 1; z < 5; ++z) //action
            {
                receiver.addListener (this, "/myo" + I + myoDataIn[y] + action[z]);
            }
        }
    }
}

OSC::~OSC()
{
}

// ==============   SENDER   ==============

void OSC::connectSender()
{
    if (! sender.connect (hostAddress, oscPortSender))
        AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                          "OSC Sender",
                                          "Myo Mapper could not connect to UDP port " + String(oscPortSender) + ".",
                                          "OK");
    oscConnectionSender = true;
}

void OSC::disconnectSender()
{
    sender.disconnect();
    oscConnectionSender = false;
}

void OSC::setSender (String HostAddress, int Port)
{
    oscPortSender = Port;
    hostAddress = HostAddress;
}

void OSC::sendOSC (int id,
                   std::array<int8_t, 8> emgRaw,
                   std::array<float, 8> emgScaled,
                   std::array<float, 8> emgScaledAbs,
                   std::array<float, 8> emgScaledAbsMavg,
                   std::array<int, 8> emgZeroCross,
                   std::array<float, 4> quaternion,
                   float mav,
                   float mavFod,
                   float emgMavMavg,
                   Vector3D<float> gyro,
                   Vector3D<float> gyroFod,
                   Vector3D<float> gyroScaled,
                   Vector3D<float> gyroScaledAbs,
                   Vector3D<float> gyroScaledFod,
                   Vector3D<float> acceleration,
                   Vector3D<float> accelerationFod,
                   Vector3D<float> accelerationScaled,
                   Vector3D<float> accelerationScaledFod,
                   Vector3D<float> orientationRaw,
                   Vector3D<float> orientationScaled,
                   Vector3D<float> orientationFod,
                   Vector3D<float> orientationSod,
                   String pose,
                   int poseID
                  )
{
    String ID = String (id);
    
    sender.send ("/myo" + ID + "/orientation/quaternion",
                 (float) quaternion[0],
                 (float) quaternion[1],
                 (float) quaternion[2],
                 (float) quaternion[3]);
    sender.send ("/myo" + ID + "/orientation/raw",
                 (float) orientationRaw.x,
                 (float) orientationRaw.y,
                 (float) orientationRaw.z);
    sender.send ("/myo" + ID + "/orientation/scaled",
                 (float) orientationScaled.x,
                 (float) orientationScaled.y,
                 (float) orientationScaled.z);
    sender.send ("/myo" + ID + "/orientation/velocity",
                 (float) orientationFod.x,
                 (float) orientationFod.y,
                 (float) orientationFod.z);
    sender.send ("/myo" + ID + "/orientation/acceleration",
                 (float) orientationSod.x,
                 (float) orientationSod.y,
                 (float) orientationSod.z);
    
    sender.send ("/myo" + ID + "/gyro/raw",
                 (float) gyro.x,
                 (float) gyro.y,
                 (float) gyro.z);
    sender.send ("/myo" + ID + "/gyro/rawFod",
                 (float) gyroFod.x,
                 (float) gyroFod.y,
                 (float) gyroFod.z);
    sender.send ("/myo" + ID + "/gyro/scaled",
                 (float) gyroScaled.x,
                 (float) gyroScaled.y,
                 (float) gyroScaled.z);
    sender.send ("/myo" + ID + "/gyro/scaledAbs",
                 (float) gyroScaledAbs.x,
                 (float) gyroScaledAbs.y,
                 (float) gyroScaledAbs.z);
    sender.send ("/myo" + ID + "/gyro/scaledFod",
                 (float) gyroScaledFod.x,
                 (float) gyroScaledFod.y,
                 (float) gyroScaledFod.z);
    
    sender.send ("/myo" + ID + "/acceleration/raw",
                 (float) acceleration.x,
                 (float) acceleration.y,
                 (float) acceleration.z);
    sender.send ("/myo" + ID + "/acceleration/rawFod",
                 (float) accelerationFod.x,
                 (float) accelerationFod.y,
                 (float) accelerationFod.z);
    sender.send ("/myo" + ID + "/acceleration/scaled",
                 (float) accelerationScaled.x,
                 (float) accelerationScaled.y,
                 (float) accelerationScaled.z);
    sender.send ("/myo" + ID + "/acceleration/scaledFod",
                 (float) accelerationScaledFod.x,
                 (float) accelerationScaledFod.y,
                 (float) accelerationScaledFod.z);
    
    sender.send ("/myo" + ID + "/EMG/raw",
                 (int) emgRaw[0],
                 (int) emgRaw[1],
                 (int) emgRaw[2],
                 (int) emgRaw[3],
                 (int) emgRaw[4],
                 (int) emgRaw[5],
                 (int) emgRaw[6],
                 (int) emgRaw[7]);
    sender.send ("/myo" + ID + "/EMG/scaled",
                 (float) emgScaled[0],
                 (float) emgScaled[1],
                 (float) emgScaled[2],
                 (float) emgScaled[3],
                 (float) emgScaled[4],
                 (float) emgScaled[5],
                 (float) emgScaled[6],
                 (float) emgScaled[7]);
    sender.send ("/myo" + ID + "/EMG/scaledAbs",
                 (float) emgScaledAbs[0],
                 (float) emgScaledAbs[1],
                 (float) emgScaledAbs[2],
                 (float) emgScaledAbs[3],
                 (float) emgScaledAbs[4],
                 (float) emgScaledAbs[5],
                 (float) emgScaledAbs[6],
                 (float) emgScaledAbs[7]);
    sender.send ("/myo" + ID + "/EMG/scaledAbsMavg",
                 (float) emgScaledAbsMavg[0],
                 (float) emgScaledAbsMavg[1],
                 (float) emgScaledAbsMavg[2],
                 (float) emgScaledAbsMavg[3],
                 (float) emgScaledAbsMavg[4],
                 (float) emgScaledAbsMavg[5],
                 (float) emgScaledAbsMavg[6],
                 (float) emgScaledAbsMavg[7]);
    sender.send ("/myo" + ID + "/EMG/ZeroCrossing",
                 (float) emgZeroCross[0],
                 (float) emgZeroCross[1],
                 (float) emgZeroCross[2],
                 (float) emgZeroCross[3],
                 (float) emgZeroCross[4],
                 (float) emgZeroCross[5],
                 (float) emgZeroCross[6],
                 (float) emgZeroCross[7]);
    sender.send ("/myo" + ID + "/EMG/mav", (float) mav);
    sender.send ("/myo" + ID + "/EMG/mav", (float) mav);
    sender.send ("/myo" + ID + "/EMG/fod", (float) mavFod);
    sender.send ("/myo" + ID + "/EMG/mavMavg",
                 (float) emgMavMavg);
    sender.send ("/myo" + ID + "/pose", (int) poseID, (String) pose);
}

// ============== END SENDER ==============


// ==============  RECEIVER  ==============

void OSC::setReceiver (int Port){
    oscPortReceiver = Port;
}

void OSC::connectReceiver()
{
    if (! receiver.connect (oscPortReceiver))
        AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                          "OSC Receiver",
                                          "Myo Mapper could not connect to UDP port " + String(oscPortReceiver) + ".",
                                          "OK");
    
    oscConnectionReceiver = true;
}

void OSC::disconnectReceiver()
{
    receiver.disconnect();
    oscConnectionReceiver = false;
}

void OSC::oscMessageReceived (const OSCMessage& message)
{
    
    // ---------------- Vibrate
    
    if (message.getAddressPattern() == "/myo" + Id + action[0])
        if (message.size() == 1 && message[0].isString())
        {
            vibrationType =  message[0].getString();
            vibrate = true;
        }
    
    for (int i = 0; i < 4; ++i) // myoDataIn
    {
        // ---------------- Centre
        
        if (message.getAddressPattern() == "/myo" + Id + myoDataIn[i] + action[1])
        {
            if (message.size() == 1 && message[0].isString())
            {
                if (message[0].getString() == "centre")
                {
                    map[i][1] = true;
                }
            }
        }
        
        // ---------------- Reverse
        
        if (message.getAddressPattern() == "/myo" + Id + myoDataIn[i] + action[4])
        {
            if (message.size() == 1 && message[0].isInt32())
            {
                if (message[0].getInt32() == 1)
                {
                    reverseStatus = true;
                }
                else if (message[0].getInt32() == 0)
                {
                    reverseStatus = false;
                }
            }
            else if (message.size() == 1 && message[0].isFloat32())
            {
                if (message[0].getFloat32() == 1)
                {
                    reverseStatus = true;
                }
                else if (message[0].getFloat32() == 0)
                {
                    reverseStatus = false;
                }
            }
            map[i][4] = true;
        }
        
        for (int y = 2; y < 4; ++y) // action
        {
            // ---------------- Set MinMax
            
            String matchString = "/myo"+Id+myoDataIn[i]+action[y];
            
            if (message.getAddressPattern() == matchString)
            {
                if (message.size() == 1)
                {
                    if (message[0].isInt32())
                    {
                        value = message[0].isInt32();
                    }
                    else if (message[0].isFloat32())
                    {
                        value = message[0].getFloat32();
                    }
                    map[i][y] = true;
                }
            }
        }
    }
}

void OSC::setMyoIdReceiver(int ID)
{
    Id = String(ID);
}




