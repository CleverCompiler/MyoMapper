#pragma once
#include "../../JuceLibraryCode/JuceHeader.h"

class MyoMapperLookAndFeel    : public LookAndFeel_V4
{
public:
    MyoMapperLookAndFeel();
    ~MyoMapperLookAndFeel();

    void drawLabel (Graphics&, Label&) override;
    Button* createSliderButton (Slider&, bool isIncrement) override;
    void drawButtonText (Graphics& g, TextButton& button, bool /*isMouseOverButton*/, bool /*isButtonDown*/) override;
    Slider::SliderLayout getSliderLayout (Slider& slider) override;
    
    void setupColours();
    Font getFont (String fontWidth);
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyoMapperLookAndFeel)
};
