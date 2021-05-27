/*
  ==============================================================================

    CircularBuffer.cpp
    Created: 18 Nov 2020 7:54:50pm
    Author:  Felix

  ==============================================================================
*/

#include "CircularBuffer.h"


CircularBuffer::CircularBuffer()
{
    buff = juce::AudioSampleBuffer();
    write = read = delaylength = 0;
}

CircularBuffer::CircularBuffer(int buffersize, int delaylength)
{
    buff = juce::AudioSampleBuffer(1,buffersize);
    buff.clear();
    write = delaylength;
    read = 0;
    this->delaylength = delaylength;

}

float CircularBuffer::getData()
{

    return buff.getSample(0, read);
    

}

void CircularBuffer::setData(float ting)
{
    buff.setSample(0, write, ting);
     
}

 void CircularBuffer::nextSample()
{
    int bufferlength = buff.getNumSamples();

    read = ((bufferlength + write) - delaylength) % bufferlength;
    write = (write + 1) % bufferlength;
}

