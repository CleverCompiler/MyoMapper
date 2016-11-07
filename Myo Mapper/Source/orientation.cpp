/*
  ==============================================================================

    orientation.cpp
    Created: 10 Jun 2016 10:33:13am
    Author:  Jamie Bullock

  ==============================================================================
*/

#include "orientation.h"

Orientation::Orientation()
{
    addAndMakeVisible(rescaleYaw);
    addAndMakeVisible(rescalePitch);
    addAndMakeVisible(rescaleRoll);
    rescaleYaw.setLabelWidget("Yaw");
    rescalePitch.setLabelWidget("Pitch");
    rescaleRoll.setLabelWidget("Roll");
    rescaleYaw.setTargetValue(0.5),
    rescalePitch.setTargetValue(0.5);
    rescaleRoll.setTargetValue(0.5);
}

void Orientation::paint(juce::Graphics &g)
{
    g.fillAll(Colours::lightgrey);   // clear the background
    g.setColour(Colours::grey);
    g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 5, 5);
    g.setColour(Colours::black);
    g.setFont(getHeight()*0.07);
    g.drawText("Orientation", getLocalBounds(),
               Justification::centredTop, true);   // draw some placeholder text
}

void Orientation::resized()
{
    rescaleYaw.setBounds(10, getHeight()*0.1, getRight()-30, getHeight()*0.28);
    rescalePitch.setBounds(rescaleYaw.getX(), rescaleYaw.getBottom()+7, rescaleYaw.getWidth(), rescaleYaw.getHeight());
    rescaleRoll.setBounds(rescaleYaw.getX(), rescalePitch.getBottom()+7, rescaleYaw.getWidth(), rescaleYaw.getHeight());
}

void Orientation::setValues(Vector3D< float > Orientation)
{
    rescaleYaw.setValue(Orientation.x);
    rescalePitch.setValue(Orientation.y);
    rescaleRoll.setValue(Orientation.z);
}

Vector3D<float> Orientation::getValue()
{
    orientationScaled.x = rescaleYaw.getValue();
    orientationScaled.y = rescalePitch.getValue();
    orientationScaled.z = rescaleRoll.getValue();
    
    return orientationScaled;
}

Vector3D<float> Orientation::getWl(){
    
    orientationWl.x = std::abs(factor.x-rescaleYaw.getValue());
    orientationWl.y = std::abs(factor.y-rescalePitch.getValue());
    orientationWl.z = std::abs(factor.y-rescaleRoll.getValue());

    factor.x = rescaleYaw.getValue();
    factor.y = rescalePitch.getValue();
    factor.z = rescaleRoll.getValue();
    
    return orientationWl;
    
    std::cout << "orientation WL: " << &orientationWl << std::endl;
}

float Orientation::getYaw()
{
    return rescaleYaw.getValue();
}

float Orientation::getPitch()
{
    return rescalePitch.getValue();
}

float Orientation::getRoll()
{
    return rescaleRoll.getValue();
}

void Orientation::map(int myoData, int Action, float Value, bool ReverseStatus)
{
    switch (myoData) {
        case 0:
            switch (Action) {
                case 1: rescaleYaw.setCentre(); break;
                case 2: rescaleYaw.setMin(Value); break;
                case 3: rescaleYaw.setMax(Value); break;
                case 4: rescaleYaw.setReverse(ReverseStatus); break;
                default:
                    break;
            }
            break;
        case 1:
            switch (Action) {
                case 1: rescalePitch.setCentre(); break;
                case 2: rescalePitch.setMin(Value); break;
                case 3: rescalePitch.setMax(Value); break;
                case 4: rescalePitch.setReverse(ReverseStatus); break;
                default:
                    break;
            }
            break;
        case 2:
            switch (Action) {
                case 1: rescaleRoll.setCentre(); break;
                case 2: rescaleRoll.setMin(Value); break;
                case 3: rescaleRoll.setMax(Value); break;
                case 4: rescaleRoll.setReverse(ReverseStatus); break;
                default:
                    break;
            }
        default:
        break;
    }
}

