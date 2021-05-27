/*
  ==============================================================================

    CustomLookh
    Created: 18 Jan 2021 10:40:48am
    Author:  Felix

  ==============================================================================
*/
#include <JuceHeader.h>
#pragma once

class NewLookAndFeel : public juce::LookAndFeel_V4
{
   

public: 

    NewLookAndFeel();
    
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override;
    
    const Font setCustomFontAndSize(float size);
    const Font loadCustomFont();
    Typeface::Ptr getTypefaceForFont();
    Font getSliderPopupFont(Slider&) override;

private:




};