#include "MainComponent.h"
#include "Myo/MyoData.h"

MainComponent::MainComponent()
{
    osc.connectReceiver();
}

MainComponent::~MainComponent()
{
    #if JUCE_MAC
        MenuBarModel::setMacMainMenu (nullptr);
    #endif
    PopupMenu::dismissAllActiveMenus();
}

void MainComponent::paint(juce::Graphics &g)
{
    /*
    if (settingsPannel.getOSCsettingsStatusSender())
    {
        osc.disconnectSender();
        osc.setSender (settingsPannel.getHostAddress(), settingsPannel.getOSCPortSender());
        settingsPannel.setOSCsettingsStatusSender (false);
        osc.connectSender();
    }

    if (settingsPannel.getOSCsettingsStatusReceiver())
    {
        osc.disconnectReceiver();
        osc.setReceiver (settingsPannel.getOSCPortReceiver());
        settingsPannel.setOSCsettingsStatusReceiver (false);
        osc.connectReceiver();
    }
    
    g.fillAll(Colours::grey);
     */
}

void MainComponent::timerCallback()
{
    bool success = false;
    std::vector<MyoData> myoData = myoManager.getMyoData (success);

    uint8 id = 1;
    
    // Update UI
    orientation.setValues (myoData[id].orientationRaw);
    pose.setPoseLabel (myoData[id].pose + " - " + String (myoData[id].poseID));

    //
    myoData[id].orientationScaled = orientation.getValue();
    myoData[id].orientationScaledFod = orientation.getFod();
    myoData[id].orientationScaledSod = orientation.getSod();
 
    if (osc.vibrate && VibrationState)
    {
        myoManager.vibrate (osc.vibrationType, true);
        osc.vibrate = false;
    }

    for (int i = 0; i < 4; ++i) // myoData
    {
        for (int y = 1; y < 5; ++y) // action
        {
            if (osc.map[i][y])
            {
                orientation.map (i, y, osc.value, osc.reverseStatus);
                osc.map[i][y] = false;
            }
        }
    }
}
/*
void MainComponent::disconnectMyoAndOSC()
{
    myoManager.disconnect();
    osc.disconnectSender();
    osc.disconnectReceiver();
}
*/
