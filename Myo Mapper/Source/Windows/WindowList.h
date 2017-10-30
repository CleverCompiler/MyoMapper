/*
  ==============================================================================

    WindowsList.h
    Created: 22 Sep 2017 3:51:10am
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "VisualsWindow.h"
#include "SettingsWindow.h"
#include "DataSelectorWindow.h"
#include "WindowDrawer.h"

//==============================================================================
/*
*/
class WindowList    :  public ChangeListener,
                       public ChangeBroadcaster
{
public:
    WindowList();
    
    static WindowList& getWindowList();
    
    void createInitialWindow();
    void showOrCreateSettingsWindow();
    void showOrCreateVisualsWindow();
    void showOrCreateDataSelectorWindow();
    
    void changeListenerCallback (ChangeBroadcaster*);
    void closeWindow (WindowDrawer*);
    
    void forceCloseWindows();
    void askAllWindowsToClose();
    
    OwnedArray<Component> windows;
private:
    DataSelectorWindow::SafePointer<Component> settingsWindow;
    DataSelectorWindow::SafePointer<Component> visualsWindow;
    DataSelectorWindow::SafePointer<Component> dataSelectorWindow;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WindowList)
};
