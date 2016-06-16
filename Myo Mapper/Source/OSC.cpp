/*
  ==============================================================================

    OSC.cpp
    Created: 14 Jun 2016 4:33:38pm
    Author:  Balandino Di Donato

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "OSC.h"
#include "MyoData.h"

//==============================================================================
OSC::OSC()
:
vibrate(false),
vibrationType("null"),
centreYaw(false),
centrePitch(false),
centreRoll(false),
centreMav(false),
rescaleMinTest(false),
rescaleMIN(0),
rescaleMaxTest(false),
rescaleMAX(0),
oscPortSender(5432),
oscPortReceiver(5431),
hostAddress("127.0.0.1"),
oscConnectionSender(false),
oscConnectionReceiver(false),
Id("0"),
myoDataIn{"/yaw", "/pitch", "/roll", "/mav"},
action{"/vibrate", "/centre", "/setMin", "/setMax"}
{
    for(int i = 0; i<4; i++) // id
    {
        String I = String(i);

        receiver.addListener(this, "/myo/"+I+action[0]);

        for(int y =0; y<4; y++) // myo data
        {
            for(int z=1; z<4; z++)
            {
                receiver.addListener(this, "/myo/"+I+myoDataIn[y]+action[z]);
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
                                          "Myo Mapper could not connect to UDP port "+String(oscPortSender)+".",
                                          "OK");
    oscConnectionSender = true;
}

void OSC::disconnectSender()
{
    sender.disconnect();
    oscConnectionSender = false;
}

void OSC::setSender(String HostAddress, int Port){
    oscPortSender = Port;
    hostAddress = HostAddress;
}

void OSC::sendOSC(int id,
                  std::array<int8_t, 8> emgRaw,
                  std::array<float, 8> emgScaled,
                  float mav,
                  Vector3D< float > gyro,
                  Vector3D< float > acceleration,
                  Vector3D< float > orientationRaw,
                  Vector3D< float > orientationScaled,
                  String pose,
                  int poseID
                  )
{
    String ID = String (id+1);
    
    sender.send ("/myo"+ID+"/emgRaw", (int) emgRaw[0], (int) emgRaw[1], (int) emgRaw[2], (int) emgRaw[3], (int) emgRaw[4], (int) emgRaw[5], (int) emgRaw[6], (int) emgRaw[7]);
    sender.send ("/myo"+ID+"/emgScaled", (float) emgScaled[0], (float) emgScaled[1], (float) emgScaled[2], (float) emgScaled[3], (float) emgScaled[4], (float) emgScaled[5], (float) emgScaled[6], (float) emgScaled[7]);
    sender.send("/myo"+ID+"/mav", (float) mav);
    sender.send("/myo"+ID+"/gyro", (float) gyro.x, (float) gyro.y, (float) gyro.z);
    sender.send("/myo"+ID+"/acceleration", (float) acceleration.x, (float) acceleration.y, (float) acceleration.z);
    sender.send("/myo"+ID+"/orientationRaw", (float) orientationRaw.x, (float) orientationRaw.y, (float) orientationRaw.z);
    sender.send("/myo"+ID+"/orientationScaled", (float) orientationScaled.x, (float) orientationScaled.y, (float) orientationScaled.z);
    sender.send("/myo"+ID+"/pose", (int) poseID, (String) pose);
}

// ============== END SENDER ==============


// ==============  RECEIVER  ==============

void OSC::setReceiver(int Port){
    oscPortReceiver = Port;
}

void OSC::connectReceiver()
{
    if (! receiver.connect (oscPortReceiver))
        AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                          "OSC Receiver",
                                          "Myo Mapper could not connect to UDP port "+String(oscPortReceiver)+".",
                                          "OK");
    
    oscConnectionReceiver = true;
}

void OSC::disconnectReceiver()
{
    receiver.disconnect();
    oscConnectionReceiver = false;
}

void OSC::oscMessageReceived(const OSCMessage& message)
{
    
// ---------------- Vibrate
    
    if (message.getAddressPattern() == "/myo/"+Id+action[1])
        if (message.size() == 1 && message[0].isString())
        {
            vibrationType =  message[0].getString();
            vibrate = true;
            std::cout << "vibrate: " << message[0].getString() << std::endl;
        }
    
    for(int i = 0; i<4; i++) // myoDataIn
    {
        for(int y=1; y<4; y++) // action
        {
            // ---------------- Centre
            
            if (message.getAddressPattern() == "/myo/"+Id+myoDataIn[i]+action[y])
            {
                std::cout << "Centre: i" << i << " y" << y << "patt: " << "/myo/"+Id+myoDataIn[i]+action[y] << std::endl;

                if (message.size() == 1 && message[0].isString())
                {
                    if (message[0].getString() == "centre")
                    {
                        map[i][y] = true;
                    }
                }
            }
            
            // ---------------- Set MinMax
            
            if (message.getAddressPattern() == "/myo/"+Id+myoDataIn[i]+action[y])
                if (message.size() == 1)
                    if (message[0].isInt32())
                    {
                        value = message[0].isInt32();
                        map[i][y] = true;
                        std::cout << "set: i" << i << " y " << y << std::endl;
                    }
                    else if (message[0].isFloat32())
                    {
                        value = message[0].isFloat32();
                        map[i][y] = true;
                        std::cout << "set: i" << i << " y " << y << std::endl;
                    }
            }
        }
    }
        
//        
//        if (message.getAddressPattern() == "/myo/"+Id+"/"+myoDataIn+"/centre")
//            if (message.size() == 1)
//                if (message[0].isString())
//                    map[0][i] = true;
//
//// ---------------- SET MIN
//        
//        if (message.getAddressPattern() == "/myo/"+Id+"/"+myoDataIn+"/setMin")
//            if (message.size() == 1)
//                if (message[0].isInt32())
//                    {
//                        map[1][i] = true;
//                        std::cout << myoDataIn << " set Min float: " << message[0].getFloat32() << std::endl;
//                    }
//                if (message[0].isFloat32())
//                    {
//                        map[1][i] = true;
//                        std::cout << myoDataIn << " set Min float: " << message[0].getFloat32() << std::endl;
//                    }
//
//// ---------------- SET MAX
//
//        if (message.getAddressPattern() == "/myo/"+Id+"/"+myoDataIn+"/setMin")
//            if (message.size() == 1)
//                if (message[0].isString())
//                    if(i==0)
//                    {
//                        std::cout << myoDataIn << " set Max float: " << message[0].getFloat32() << std::endl;
//                    }
//                    else if(i==1)
//                    {
//                        std::cout << myoDataIn << " set Max float: " << message[0].getFloat32() << std::endl;
//                    }
//                    else if(i==2)
//                    {
//                        std::cout << myoDataIn << " set Max float: " << message[0].getFloat32() << std::endl;
//                    }
//
//    }
//}

void OSC::setMyoIdReceiver(int ID)
{
    Id = String(ID);
}


