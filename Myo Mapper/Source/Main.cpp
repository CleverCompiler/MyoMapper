#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"

//==============================================================================
class MyoMapperApplication  : public JUCEApplication
{
public:
    //==============================================================================
    MyoMapperApplication() {}

    const String getApplicationName() override       { return ProjectInfo::projectName; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { return true; }

    //==============================================================================
    void initialise (const String& commandLine) override
    {
        mainWindow = new MainWindow (getApplicationName());
        
    
    }

    void shutdown() override
    {
        mainWindow = nullptr; // (deletes our window)
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        quit();
    }

    void anotherInstanceStarted (const String& commandLine) override
    {
        // here is where we can put the option of opening another instance for a second myo
    }

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainContentComponent class.
    */
    class MainWindow    : public DocumentWindow
    {
    public:
        MainWindow (String name)  : DocumentWindow (name,
                                                    Colours::lightgrey,
                                                    DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (new MainComponent(), true);

            setCentrePosition(getWidth()*0.5, 0);
            setVisible (true);
            setResizable(true, true);
            setResizeLimits(getParentWidth()*0.6, getParentHeight(), getParentWidth(), getParentHeight());
        }

        void closeButtonPressed() override
        {
            // This is called when the user tries to close this window. Here, we'll just
            // ask the app to quit when this happens, but you can change this to do
            // whatever you need.
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content component instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    ScopedPointer<MainWindow> mainWindow;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (MyoMapperApplication)
