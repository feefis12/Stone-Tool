/*
  ==============================================================================

    DelayBuffer.h
    Created: 24 Dec 2020 7:47:45pm
    Author:  Felix

  ==============================================================================
*/
#include <JuceHeader.h>
#pragma once


class DelayBuff
{
public:
    DelayBuff();

    void setBufferSize(float sampleRate);
    void setIn(float in);
    //void setOut(float out);
    void setRead(float read);
    float getOut();
    float getIn();
    void Process();

private:

    std::vector<float> pBuffer;
    int read;
    int write;


};