/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomLook.h"
#include "ClickSlider.h"




//==============================================================================
/**
*/
class Stone_ToolAudioProcessorEditor  : public juce::AudioProcessorEditor, 
{
public:
    Stone_ToolAudioProcessorEditor (Stone_ToolAudioProcessor&);
    ~Stone_ToolAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
 
private:
    float PrevChoice;
    
    Slider Pre;
    Slider Tone;
    Slider Drive;
    Slider Wide;
    NewLookAndFeel N_look;
    ImageComponent monkey;
    Label d_label;
    Label c_label;
    Label t_label;
  
    MySlider D2;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> A_pre;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> A_2nd;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> A_tone;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> A_drive;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> A_wide;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Stone_ToolAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Stone_ToolAudioProcessorEditor)
};
