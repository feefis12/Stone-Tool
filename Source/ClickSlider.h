/*
  ==============================================================================

    ClickSlider.h
    Created: 23 Jan 2021 6:46:28pm
    Author:  Felix

  ==============================================================================
  */
#include <JuceHeader.h>

#pragma once
class MySlider : public juce::Slider
{
public:
    MySlider();
    
    void MySlider::mouseDown(const MouseEvent& e) override;
    float MySlider::returnInvert();

private:
    std::unique_ptr<PopupMenu> p;
    int choice;

};