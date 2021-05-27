/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Stone_ToolAudioProcessorEditor::Stone_ToolAudioProcessorEditor(Stone_ToolAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    /* box1.setSelectedItemIndex(1);
     box1.addItem("OverDrive", 1);
     box1.addItem("HardClip", 2);
     addAndMakeVisible(box1);
     box1.addListener(this);*/
     /* A_wide = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "WIDE", Wide);*/
    A_tone = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "TONE", Tone);
    A_pre = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "PREGAIN", Pre);
    A_drive = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "DIST", Drive);
    A_2nd = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "casecade", D2);



    setLookAndFeel(&N_look);
    D2.addComponentListener(this);

    ///LABEL///
    d_label.setText("GAIN", NotificationType::dontSendNotification);
    addAndMakeVisible(d_label);

    c_label.setText("DRIVE", NotificationType::dontSendNotification);
    addAndMakeVisible(c_label);

    t_label.setText("TONE", NotificationType::dontSendNotification);
    addAndMakeVisible(t_label);
    d_label.setFont(N_look.setCustomFontAndSize(30));
    t_label.setFont(N_look.setCustomFontAndSize(30));
    c_label.setFont(N_look.setCustomFontAndSize(30));

    ///SLIDER///
    D2.setRotaryParameters(juce::MathConstants<float>::pi * 1.2f, juce::MathConstants<float>::pi * 2.8f, true);
    D2.setDoubleClickReturnValue(true, 0.0);
    D2.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    D2.setTextBoxStyle(Slider::NoTextBox, 0, 0, 0);
    D2.setSkewFactor(5, false);

    addAndMakeVisible(D2);

    Drive.setRotaryParameters(juce::MathConstants<float>::pi * 1.2f, juce::MathConstants<float>::pi * 2.8f, true);
    Drive.setDoubleClickReturnValue(true, 0.0);
    Drive.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    Drive.setTextBoxStyle(Slider::NoTextBox, 0, 0, 0);
    Drive.setSkewFactor(1, false);
    addAndMakeVisible(Drive);

    Pre.setDoubleClickReturnValue(true, 0.0);
    Pre.setRotaryParameters(juce::MathConstants<float>::pi * 1.2f, juce::MathConstants<float>::pi * 2.8f, false);
    Pre.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    Pre.setTextBoxStyle(Slider::NoTextBox, 0, 0, 0);
    Pre.setColour(juce::Slider::thumbColourId, juce::Colours::black);

    Tone.setDoubleClickReturnValue(true, 0.0);
    Tone.setRotaryParameters(juce::MathConstants<float>::pi * 1.2f, juce::MathConstants<float>::pi * 2.8f, true);
    Tone.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    Tone.setTextBoxStyle(Slider::NoTextBox, 0, 0, 0);
    Tone.setSkewFactor(500, false);
    addAndMakeVisible(Tone);
  
  /*  if (D2.returnInvert() != 0)
    {
        audioProcessor.u_i = 1;
    }
    
    addAndMakeVisible(audioProcessor.v);*/


    /*Invert_m.addItem(1, "Invert", true, true);
    Invert_m.show(0, 1, 1, 1, nullptr);*/
    setSize(400, 300);

}

Stone_ToolAudioProcessorEditor::~Stone_ToolAudioProcessorEditor()
{
    setLookAndFeel(nullptr);

}

//==============================================================================
void Stone_ToolAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    juce::Image background = juce::ImageCache::getFromMemory(BinaryData::monkey_jpg, BinaryData::monkey_jpgSize);

    g.drawImageAt(background, 0, 0);



}

void Stone_ToolAudioProcessorEditor::resized()
{
    D2.setBounds(150, 100, 100, 100);
    Tone.setBounds(290, 100, 100, 100);
    /*  Wide.setBounds(100, 50, 100, 100);*/
    Drive.setBounds(20, 100, 100, 100);
  /*  audioProcessor.v.setBounds(100, 100, 100, 100);*/
    d_label.setBounds(40, 170, 100, 100);
    c_label.setBounds(160, 170, 100, 100);
    t_label.setBounds(300, 170, 100, 100);
}

