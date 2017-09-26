/*
  ==============================================================================

    SettingsWindow.h
    Created: 22 Sep 2017 5:08:54pm
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#pragma once

class WindowList;

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Application.h"

//==============================================================================
/*
*/


class SettingsWindow    : public Component,
                          private Button::Listener
{
public:
    SettingsWindow();
    ~SettingsWindow();

    void paint (Graphics&) override;
    void resized() override;
    void buttonClicked (Button*) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsWindow)
    LookAndFeel_V3 toggleButtonLAF;
    
    Label oscSendLabel;
    Slider oscSendSetter;
    Label oscReceiveLabel;
    Slider oscReceiveSetter;
    
    Label myoSelectorLabel;
    ComboBox myoSelectorSetter;
    
    ToggleButton orientationToggle;
    ToggleButton accelerationToggle;
    ToggleButton gyroToggle;
    ToggleButton emgToggle;
    ToggleButton poseToggle;
    
    TextButton saveButton;
    TextButton openButton;
    ToggleButton hideOnStartupButton;
    TextButton startButton;
    
    ToggleButton testButton;
    
    
//    Label hostAddressTitle;
};
