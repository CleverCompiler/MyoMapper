/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.1.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "OSCsettings.h"
#include "orOSCsettings.h"
#include "accOSCsettings.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
OSCsettings::OSCsettings ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (oscSettingsTab = new TabbedComponent (TabbedButtonBar::TabsAtTop));
    oscSettingsTab->setTabBarDepth (30);
    oscSettingsTab->addTab (TRANS("Orientation"), Colours::lightgrey, new orOSCsettings(), true);
    oscSettingsTab->addTab (TRANS("Accelerometer"), Colours::lightgrey, new accOSCsettings(), true);
    oscSettingsTab->addTab (TRANS("Gyroscope"), Colours::lightgrey, 0, false);
    oscSettingsTab->addTab (TRANS("EMG"), Colours::lightgrey, 0, false);
    oscSettingsTab->setCurrentTabIndex (0);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

OSCsettings::~OSCsettings()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    oscSettingsTab = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void OSCsettings::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffaeaeae));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void OSCsettings::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    oscSettingsTab->setBounds (0, 0, proportionOfWidth (1.0000f), proportionOfHeight (1.0000f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="OSCsettings" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffaeaeae"/>
  <TABBEDCOMPONENT name="oscSettingsTab" id="96fad8a2b41af81d" memberName="oscSettingsTab"
                   virtualName="" explicitFocusOrder="0" pos="0 0 100% 100%" orientation="top"
                   tabBarDepth="30" initialTab="0">
    <TAB name="Orientation" colour="ffd3d3d3" useJucerComp="1" contentClassName=""
         constructorParams="" jucerComponentFile="orOSCsettings.cpp"/>
    <TAB name="Accelerometer" colour="ffd3d3d3" useJucerComp="1" contentClassName=""
         constructorParams="" jucerComponentFile="accOSCsettings.h"/>
    <TAB name="Gyroscope" colour="ffd3d3d3" useJucerComp="0" contentClassName=""
         constructorParams="" jucerComponentFile=""/>
    <TAB name="EMG" colour="ffd3d3d3" useJucerComp="0" contentClassName=""
         constructorParams="" jucerComponentFile=""/>
  </TABBEDCOMPONENT>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
