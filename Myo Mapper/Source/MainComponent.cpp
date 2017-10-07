#include "MainComponent.h"
#include "MyoData.h"

MainComponent::MainComponent()
:   selectedMyoID (0)
{
    setSize (getParentWidth() * 0.4, getParentHeight());

    getLookAndFeel().setUsingNativeAlertWindows (true);
    
    addAndMakeVisible (orientation);
    // used
//    orientation.setVisible (MyoMapperApplication::getAppProperties().getUserSettings()->getBoolValue ("Show Orientation", false));
    addAndMakeVisible (settingsPannel);
    addAndMakeVisible (pose);
    // used
//    pose.setVisible MyoMapperApplication::getAppProperties().getUserSettings()->getBoolValue ("Show Pose", false));
    
    settingsPannel.showOrientation.addListener (this);
    settingsPannel.showPose.addListener (this);
    
    settingsPannel.myoList.addListener (this);
    myoManager.connect();
    myoManager.startPoll();
    
    osc.setSender(settingsPannel.getHostAddress(), settingsPannel.getOSCPortSender());
    osc.connectSender();
    osc.connectReceiver();
    
    startTimer(25);
    
    // used
//    selectedMyoID = MyoMapperApplication::getAppProperties().getUserSettings()->getIntValue("Myo ID", 0);
}

MainComponent::~MainComponent()
{
//    MyoMapperApplication::getAppProperties().getUserSettings()->setValue ("Myo ID", selectedMyoID);
}

void MainComponent::paint(juce::Graphics &g)
{
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
}

void MainComponent::resized()
{
    auto area = getLocalBounds().reduced (getHeight() * 0.01);
    
    settingsPannel.setBounds (area.removeFromTop (getHeight() * 0.24));
    
    if (orientation.isVisible() == true)
    {
        orientation.setBounds (area.removeFromTop (getHeight() * 0.63));
    }
    pose.setBounds (area.removeFromTop (getHeight() * 0.12));
}

void MainComponent::buttonClicked (Button* button)
{
    if (button == &settingsPannel.showOrientation)
        setPanelVisibility (orientation);
    if (button == &settingsPannel.showPose)
        setPanelVisibility (pose);
    
    resized();
}

void MainComponent::setPanelVisibility (Component &panel)
{
    panel.setVisible (!panel.isVisible());
}

void MainComponent::timerCallback()
{
    bool success = false;
    std::vector<MyoData> myoData = myoManager.getMyoData (success);
    
    if (! success) return;
    
    if (! selectedMyoID || selectedMyoID >= myoData.size()) return;
    
    uint8 id = selectedMyoID;
        
    orientation.setValues (myoData[id].orientationRaw);
    pose.setPoseLabel (myoData[id].pose + " - " + String (myoData[id].poseID));

    osc.sendOSC (id,
                 myoData[id].emgRaw,
                 myoData[id].emgScaled,
                 myoData[id].emgScaledAbs,
                 myoData[id].emgScaledAbsMavg,
                 myoData[id].emgScaledAbsFob,
                 myoData[id].emgScaledAbsFobMavg,
                 myoData[id].emgZeroCross,
                 myoData[id].emgMin,
                 myoData[id].emgMax,
                 myoData[id].quaternion,
                 myoData[id].emgMav,
                 myoData[id].emgMavMin,
                 myoData[id].emgMavMax,
                 myoData[id].mavFod,
                 myoData[id].emgMavMavg,
                 myoData[id].mavFodMavg,
                 myoData[id].gyro,
                 myoData[id].gyroFod,
                 myoData[id].gyroScaled,
                 myoData[id].gyroScaledAbs,
                 myoData[id].gyroScaledFod,
                 myoData[id].gyroZeroCross,
                 myoData[id].acceleration,
                 myoData[id].accelerationFod,
                 myoData[id].accelerationScaled,
                 myoData[id].accelerationScaledFod,
                 myoData[id].orientationRaw,
                 orientation.getValue(),
                 orientation.getFod(),
                 orientation.getSod(),
                 myoData[id].pose,
                 myoData[id].poseID);
 
    
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

void MainComponent::disconnectMyoAndOSC()
{
    myoManager.disconnect();
    osc.disconnectSender();
    osc.disconnectReceiver();
}


void MainComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
	if (comboBoxThatHasChanged == &settingsPannel.myoList)
	{
		selectedMyoID = settingsPannel.myoList.getSelectedId();
		osc.setMyoIdReceiver (selectedMyoID);
	}

}

void MainComponent::HelpDialogWindow()
{
    HelpWindow* helpWindow = new HelpWindow ("Online Documentation",
                                             Colours::grey,
                                             DocumentWindow::closeButton);
    helpWindow->addToDesktop();
    
    Rectangle<int> area (0, 0, 300, 150);
    
    RectanglePlacement placement (RectanglePlacement::xMid
                                  | RectanglePlacement::yMid
                                  | RectanglePlacement::doNotResize);
    
    Rectangle<int> result (placement.appliedTo (area, Desktop::getInstance().getDisplays()
                                                .getMainDisplay().userArea.reduced (20)));
    helpWindow->setBounds (result);
    
    helpWindow->setResizable (false, false);
    helpWindow->setUsingNativeTitleBar (true);
    helpWindow->setVisible (true);
}
