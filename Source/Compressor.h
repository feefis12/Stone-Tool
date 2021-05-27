/*
  ==============================================================================

    Compressor.h
    Created: 19 Nov 2020 1:36:35pm
    Author:  Felix

  ==============================================================================
*/
#include "CircularBuffer.h"
#pragma once

class Compressor
{
public:
    Compressor();
    float compressSample(float data, float thres, float ratio, float attack, float release, float knee);

private: 
    CircularBuffer buffer;
    float tav, rms, gain;


};
