/*
  ==============================================================================

    CustomLook.cpp
    Created: 18 Jan 2021 10:40:48am
    Author:  Felix

  ==============================================================================
*/

#include "CustomLook.h"

NewLookAndFeel::NewLookAndFeel()
{
    setColour(juce::PopupMenu::backgroundColourId, juce::Colours::darkslategrey);
}

void NewLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&)
{
    auto radius = (float)juce::jmin(width / 2, height / 2) - 4.0f;
    auto centreX = (float)x + (float)width * 0.5f;
    auto centreY = (float)y + (float)height * 0.5f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    // fill
    g.setColour(juce::Colours::dimgrey);
    g.fillEllipse(rx, ry, rw, rw);

    // outline
    g.setColour(juce::Colours::black);
    g.drawEllipse(rx, ry, rw, rw, 1.0f);

    juce::Path p;
    auto pointerLength = radius * 0.33f;
    auto pointerThickness = 2.0f;
    p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));
    g.setColour(juce::Colours::black);
    g.fillPath(p);
   



}

const Font NewLookAndFeel::setCustomFontAndSize(float size)
{
    static auto typeface = Typeface::createSystemTypefaceFor(BinaryData::Dulethia_ttf, BinaryData::Dulethia_ttfSize);
    Font font = typeface;
    font.setHeight(size);
    
    return font;
}

const Font NewLookAndFeel::loadCustomFont()
{
    static auto typeface = Typeface::createSystemTypefaceFor(BinaryData::Dulethia_ttf, BinaryData::Dulethia_ttfSize);
    Font font = typeface;
    return font;
}

Typeface::Ptr NewLookAndFeel::getTypefaceForFont()
{
    return loadCustomFont().getTypeface();
}

Font NewLookAndFeel::getSliderPopupFont(Slider&)
{
    return Font(loadCustomFont());
}


