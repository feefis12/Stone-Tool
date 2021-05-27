    /*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#define INVERT "Invert"

//==============================================================================
Stone_ToolAudioProcessor::Stone_ToolAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), tree(*this ,nullptr,"Prams", Layout())
#endif
{
 
    
    addParameter(m_uInvertStages = new AudioParameterFloat("invert", "INVERT", 0, 1, 0));
   
}

Stone_ToolAudioProcessor::~Stone_ToolAudioProcessor()
{
  
}

//==============================================================================
const juce::String Stone_ToolAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Stone_ToolAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Stone_ToolAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Stone_ToolAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Stone_ToolAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Stone_ToolAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Stone_ToolAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Stone_ToolAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Stone_ToolAudioProcessor::getProgramName (int index)
{
    return {};
}

void Stone_ToolAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Stone_ToolAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    lastSampleRate = sampleRate;
 
    for (int channel = 0; channel < getNumOutputChannels(); channel++)
    {
        allComp.add(Compressor());
        allFil.add(IIRFilter());
        
    }
  
    blend = tree.getRawParameterValue("DIST");
    preGain = tree.getRawParameterValue("PREGAIN");
    freq = tree.getRawParameterValue("TONE");
    step2D = tree.getRawParameterValue("casecade");
    prevDrive = *tree.getRawParameterValue("DIST");
 
}

void Stone_ToolAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Stone_ToolAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Stone_ToolAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        Compressor* comp = &allComp.getReference(channel);
        IIRFilter* fil = &allFil.getReference(channel);
        
        float currentDrive = *tree.getRawParameterValue("DIST");


        for (int sample = 0; sample < buffer.getNumSamples(); sample++)
        {

            auto pre = *preGain * channelData[sample];

            if (*blend > 0)
            {

                float dry = comp->compressSample(pre, -40.0, 5, 10, 1, 100);


                float wet = 0;
                auto M_PI = MathConstants<float>::pi;
                auto z = M_PI * gain;
                auto s = 1 / sin(z);
                auto b = 1 / gain;

                if (dry > b)
                {
                    wet = 1;
                }
                else
                {
                    wet = sin(z * dry) * s;
                }
                //wet = std::atan(dry * gain) * juce::jmax(1 / std::atan(gain), 0.1f);

                int blend1 = (int)*blend;
                float blendFloat = *blend - blend1;
                int blendx1 = blend1 + 1;
                auto smoothBlend = lerp(blend1, blendx1, blendFloat);



                channelData[sample] = pre * (dry * (1.f - smoothBlend) + wet * smoothBlend);

            }

            if (*step2D > 0)
            {

                auto f_xn = channelData[sample];

                int step2 = (int)*step2D;
                float stepfloat = *step2D - step2;
                int step_x = step2 + 1;
                auto smoothStep = lerp(step2, step_x, stepfloat);

                for (int i = 0; i < smoothStep; i++)
                {
                    if (f_xn >= 0)
                        f_xn = (1.0 / atan(10)) * atan(10 * f_xn);
                    else
                        f_xn = (1.0 / atan(2)) * atan(2 * f_xn);
                    // invet every other stage
                    if (u_i == 1 && i % 2 == 0)
                        f_xn *= -1.0;

                    int blend1 = (int)*blend;
                    float blendFloat = *blend - blend1;
                    int blendx1 = blend1 + 1;
                    auto smoothBlend = lerp(blend1, blendx1, blendFloat);

                    channelData[sample] = pre * (channelData[sample] * (1.f - smoothBlend) + f_xn * smoothBlend);
                }

            }

        }

        int x_freq = (int)*freq;
        float freq_float = *freq - x_freq;
        int x1_freq = x_freq + 1;
        auto smoothFreq = lerp(x_freq, x1_freq, freq_float);

        fil->setCoefficients(IIRCoefficients::makePeakFilter(lastSampleRate, smoothFreq, 1, 70));
        fil->processSamples(channelData, buffer.getNumSamples());
       /* v.pushBuffer((const float**)channelData, buffer.getNumChannels(), buffer.getNumSamples());*/
    }
}


//==============================================================================
bool Stone_ToolAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Stone_ToolAudioProcessor::createEditor()
{
    return new Stone_ToolAudioProcessorEditor (*this);
}

float Stone_ToolAudioProcessor::lerp(float v0, float v1, float t) {
    return (1 - t) * v0 + t * v1;
}

//==============================================================================
void Stone_ToolAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = tree.copyState();
    std::unique_ptr<XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void Stone_ToolAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName(tree.state.getType()))
            tree.replaceState(ValueTree::fromXml(*xmlState));
        }

}
//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Stone_ToolAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout
Stone_ToolAudioProcessor::Layout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> p;
    p.push_back(std::make_unique<juce::AudioParameterFloat>("DIST", "dist", 0, 1, 0)),
    p.push_back(std::make_unique<juce::AudioParameterFloat>("TONE", "tone", NormalisableRange<float>(100, 2000, 100), 100)),
        /*      p.push_back(std::make_unique<juce::AudioParameterFloat>("WIDE", "wide", 0.1, 2, 0.2)),*/
    p.push_back(std::make_unique<juce::AudioParameterFloat>("PREGAIN", "preGain", 0, 10, 5)),
    p.push_back(std::make_unique<juce::AudioParameterFloat>("casecade", "cascade", 1, 10, 1));
     /*   p.push_back(std::make_unique<juce::AudioParameterFloat>("DRYWET", "drywet", 0, 1, 0.1));*/
        return {p.begin(),p.end() };
   

}

