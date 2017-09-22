#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

//#include "CommandIDs.h"
#include "Application.h"
#include "Orientation.h"
#include "Settings.h"
#include "MyoManager.h"
#include "Pose.h"
#include "OSC.h"
#include "AboutWindow.h"
#include "HelpWindow.h"
#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/*
*/
class MainComponent    : public Component,
                         private Timer,
//                         public ApplicationCommandTarget,
                         private ComboBox::Listener,
                         private Button::Listener   // Added Listener for panel show/ hide buttons
{
    
public:
    MainComponent();
    ~MainComponent();

    void paint (Graphics& g) override;
    void resized() override;
    void disconnectMyoAndOSC();

    Orientation orientation;
    
    enum MenuIDs {
        AboutMyoMapper = 1000,
        Preferences,
        OpenSettingsFromFile,
        SaveSettingsToFile,
        AddMyo,
        Quit,
        ShowOrientation,
        ShowEMGsMAV,
        ShowPose,
        onlineDocumentation
    };
    
//    ApplicationCommandTarget* getNextCommandTarget() override;
    
    Settings settingsPannel;
    void setPanelVisibility (Component &component);
    
    void AboutMyoMapperDialogWindow();
    void HelpDialogWindow();
    void buttonClicked (Button* button) override;
    
    
    
    
    
private:    
    void timerCallback() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    
    MyoManager myoManager;
    Pose pose;
    OSC osc;
    
    int selectedMyoID;
    
    MenuBarComponent menuBar;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
