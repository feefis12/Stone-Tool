/*
  ==============================================================================

    DelayBuffer.cpp
    Created: 24 Dec 2020 7:47:45pm
    Author:  Felix

  ==============================================================================
*/

#include "DelayBuffer.h"

DelayBuff::DelayBuff()
{
    read = 0.0;
    write = 0.0;
    
    //pBuffer.clear();
}

void DelayBuff::setBufferSize(float sampleRate)
{
    pBuffer.resize(2  * sampleRate);
}

void DelayBuff::setIn(float in)
{
    pBuffer[write] = in;

}

//void DelayBuff::SetOut(float out)
//{
//    out = pBuffer[read];
//}

void DelayBuff::setRead(float reat)
{
    read = (write - (int)(reat)+ pBuffer.size()) % pBuffer.size();
}

void DelayBuff::Process()
{
    write++;

    if (write >= pBuffer.size())
    {
        write = 0;

    }

    read++;

    if (read < 0)
    {
        read += pBuffer.size();
    }

   
}

float DelayBuff::getOut()
{
    return pBuffer[read];


}

float DelayBuff::getIn()
{
    return pBuffer[write];
    
}
