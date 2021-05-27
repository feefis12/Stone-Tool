#pragma once
#include <JuceHeader.h>

class CircularBuffer
{
public:
	CircularBuffer();
	CircularBuffer(int buffersize, int delaylength);
	float getData();
	void setData(float ting);
	void nextSample();


private:
	int write;
	int read;
	int delaylength;
	juce::AudioSampleBuffer buff;
};

