#include "..\..\..\JUCE\Stone_Reverb\Source\Compressor.h"
/*
  ==============================================================================

    Compressor.cpp
    Created: 19 Nov 2020 1:36:35pm
    Author:  Felix

  ==============================================================================
*/

#include "Compressor.h"


Compressor::Compressor()
{
    buffer = CircularBuffer(150, 20);
    tav = 0.01;
    rms = 0;
    gain = 1;

}



float Compressor::compressSample(float data, float thres, float ratio, float attack, float release, float knee)
{
    rms = (1 - tav) * rms + tav * std::pow(data, 2);
    float dbRMS = 10 * std::log(rms);
    float slope = 1 - (1 / ratio);
    float dbGain = std::min(0.0f, (slope * (thres - dbRMS)));
    float newGain = std::pow(10, dbGain / 20);

    float coeff;
    if (newGain < gain)
    {
        coeff = attack;
    }
    else
    {
        coeff = release;
    }

    gain = (1 - coeff) * gain + coeff * newGain; 
    float compressedSample = gain * buffer.getData();
    buffer.setData(data);
    buffer.nextSample();
    return compressedSample;

    //return 0.0f;
}
