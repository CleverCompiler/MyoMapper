/*
  ==============================================================================

    WindowDrawer.cpp
    Created: 2 Oct 2017 4:29:44pm
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "WindowDrawer.h"

#include "../Application.h"

bool WindowDrawer::wantsToClose;

//==============================================================================
WindowDrawer::WindowDrawer (const String& title,
                            Component* content,
                            bool setResizeable,
                            bool setFixedAspectRatio,
                            int minWidth, int minHeight,
                            int maxWidth, int maxHeight)
:   DialogWindow (title, Colours::white, false, true)
{
    setUsingNativeTitleBar (true);
    setResizable (setResizeable, setResizeable);
    if (setFixedAspectRatio == true)
    {
        boundsConstrainer = new (ComponentBoundsConstrainer);
        auto aspectRatio = (double)minWidth / (double)minHeight;
        boundsConstrainer->setFixedAspectRatio (aspectRatio);
        boundsConstrainer->setMinimumSize (minWidth, minHeight);
        boundsConstrainer->setMaximumSize (maxWidth, maxHeight);
        boundsConstrainer->setMinimumOnscreenAmounts (maxHeight, maxWidth, maxHeight, maxWidth);
        setConstrainer (boundsConstrainer);
    }
    else
    {
        setResizeLimits (minWidth, minHeight, maxWidth, maxHeight);
    }
    setContentOwned (content, false);
    setVisible (true);
    addKeyListener (MyoMapperApplication::getCommandManager().getKeyMappings());
}

void WindowDrawer::closeButtonPressed()
{
    wantsToClose = true;
    sendChangeMessage();
}

bool WindowDrawer::windowWantsToClose()
{
    return WindowDrawer::wantsToClose;
}
