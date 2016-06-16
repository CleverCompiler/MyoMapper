/*
  ==============================================================================

    settings.h
    Created: 9 Jun 2016 2:04:30pm
    Author:  Balandino Di Donato

  ==============================================================================
*/

#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class Settings    : public Component,
private Label::Listener,
private Slider::Listener
{
public:
    Settings();
    ~Settings();

    void paint (Graphics& g) override;
    void resized() override;
    
    void labelTextChanged(juce::Label *labelThatHasChanged) override;
    void sliderValueChanged(juce::Slider *slider) override;
    
    void vibrate();
    
    int getShowOrientation();
    int getShowPose();
    int getShowMav();
    
    bool getOSCsettingsStatusSender();
    bool getOSCsettingsStatusReceiver();

    void setOSCsettingsStatusSender(bool OSCsettingsStatusSender);
    void setOSCsettingsStatusReceiver(bool OSCsettingsStatusReceiver);
    
    int getOSCPortSender();
    int getOSCPortReceiver();
    
    String getHostAddress();
    int getSelectedMyo();
    
private:
    Slider oscPortSliderSender;
    Slider oscPortSliderReceiver;

    Label oscPortLabelSender;
    Label oscPortLabelReceiver;
    
    Label hostAddressTitle;
    Label setHostAddress;
    
    ComboBox myoList;
    
    ToggleButton showOrientation;
    ToggleButton showMav;
    ToggleButton showPose;
    
    bool oscSettingsChangedSender = false;
    bool oscSettingsChangedReceiver = false;
    
    int oscPortSender;
    int oscPortReceiver;

    String hostAddress;
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Settings)
};


#endif  // SETTINGS_H_INCLUDED
