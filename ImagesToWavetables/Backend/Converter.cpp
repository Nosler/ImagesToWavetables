#include "Converter.h"
#include "Audio/Oscillator.h"
#include "Utils/InterpolationUtils.h"
#include "../Source/MainComponent.h"
#include <JuceHeader.h>
#include <math.h>
#include <chrono>
#include <iostream>

using namespace std;
using namespace juce;
using namespace InterpolationUtils;
using namespace chrono;

Converter::Converter()
{
    IsPlaying = false;
    OscBank = NULL;
    Picture = NULL;
    ColumnData = NULL;
    OscCount = Column = 0;
    //All Pan values start centered
    UpdatePan(0, 0.5f);
    UpdatePan(1, 0.5f);
    UpdatePan(2, 0.5f);
    //All channel levels start at one third of max volume
    RedLevel = GreenLevel = BlueLevel = 0.33f;
    //We are using sums of sines, whose frequencies are scaled logarithmically
	SetOscillatorType(Sine);
	SetScaleType(Logarithmic);
}

Converter::~Converter()
{
	if (OscBank != NULL)
	{
        //TODO: this loop could be parallelized with a parallel map
		for(int i = 0; i < OscCount; i++){
			delete OscBank[i];
		}
		delete OscBank;
	}
    if(Picture != NULL)
        delete Picture;
    if(ColumnData != NULL)
        delete ColumnData;
}

void Converter::SetSampleRate(int sampleRate)
{
    //TODO: this loop could be parallelized with a parallel map
    for(int i = 0; i < OscCount; i++)
    {
        OscBank[i]->SetSampleRate(sampleRate);
    }
}

void Converter::Reset()
{
    //TODO: this loop could be parallelized with a parallel map
    for(int i = 0; i < OscCount; i++)
    {
        OscBank[i]->Position = 0.0;
    }
}

void Converter::UpdatePan(int color, float pan)
{
    switch (color)
    {
        case 0: //R
        {
            RedPan = pan;
            RatioRedLeft = Sinterp(1.0, 0.0, RedPan);
            RatioRedRight = 1.0f - RatioRedLeft;
            break;
        }
        case 1: //G
        {
            GreenPan = pan;
            RatioGreenLeft = Sinterp(1.0, 0.0, GreenPan);
            RatioGreenRight = 1.0f - RatioGreenLeft;
            break;
        }
        case 2: //B
        {
            BluePan = pan;
            RatioBlueLeft = Sinterp(1.0, 0.0, BluePan);
            RatioBlueRight = 1.0f - RatioBlueLeft;
            break;
        }
    }
}

void Converter::UpdateLevel(int color, float value)
{
    switch (color)
    {
        case 0: //R
        {
            RedLevel = value;
            break;
        }
        case 1: //G
        {
            GreenLevel = value;
            break;
        }
        case 2: //B
        {
            BlueLevel = value;
            break;
        }
    }
}

void Converter::SetColumn(int column)
{
    Column = column;
    //Loads all the column data into a float array for cache coherency/speed
    //TODO: I believe this could be parallelized with a parallel map; but I don't know how JUCE's colour class is implemented
    for(int i = 0; i < OscCount; i++)
    {
        ColumnData[i] = Picture->getPixelAt(column, OscCount - 1 - i);
    }
}

void Converter::Read(float* leftChannel, float* rightChannel)
{
    float oscValue;
    
    //TODO: This could be parallelized with a parallel reduce
    //Research OpenMP
    
    for(int i = 0; i < OscCount; i++)
    {
        oscValue = OscBank[i]->Read();
        Colour pixel = ColumnData[i];
        
        *leftChannel += oscValue *
                      (RedLevel * pixel.getFloatRed() * RatioRedLeft
                     + GreenLevel * pixel.getFloatGreen() * RatioGreenLeft
                     + BlueLevel * pixel.getFloatBlue() * RatioBlueLeft);
        
        *rightChannel += oscValue *
                       (RedLevel * pixel.getFloatRed() * RatioRedRight
                      + GreenLevel * pixel.getFloatGreen() * RatioGreenRight
                      + BlueLevel * pixel.getFloatBlue() * RatioBlueRight);
    }
    *leftChannel *= InverseHeight;
    *rightChannel *= InverseHeight;
}

void Converter::SetOscillatorType(OscillatorType type)
{
    if (OscBank != NULL)
    {
        //TODO: this loop could be parallelized with a parallel map
        for(int i = 0; i < OscCount; i++){
            OscBank[i]->SetOscillatorType(type);
        }
    }
}

void Converter::Convert(Image* image)
{
    if(Picture != NULL && image != Picture)
    {
        delete Picture;
    }
    Picture = image;
    
	if (OscBank != NULL)
	{
        //TODO: this loop could be parallelized with a parallel map
		for(int i = 0; i < OscCount; i++){
			delete OscBank[i];
		}
		delete OscBank;
		OscBank = NULL;
	}
    OscCount = Height = Picture->getHeight();
    InverseHeight = 1.0 / ((double)Height*3.0);
    Width = image->getWidth();

	OscBank = new Oscillator*[OscCount];
    
    if(ColumnData != NULL)
    {
        delete ColumnData;
        ColumnData = NULL;
    }
    
    ColumnData = new Colour[OscCount];

    //TODO: this loop could be parallelized with a parallel map
	for(int i = 0; i < OscCount; i++)
    {
        float freq = HeightToFrequency(i, Height);
		OscBank[i] = new Oscillator(freq, 1.0, 44100, OscBufferSize);
	}
	SetColumn(0);
}

static float LinearHeightToFreq(int pixelHeight, int imageHeight){
	float ratio = ((float)pixelHeight / (float)imageHeight);
	return ratio * (MAX_FREQ - MIN_FREQ) + MIN_FREQ;
}

static float ExponentialHeightToFreq(int pixelHeight, int imageHeight){
	float squarePixelHeight = pixelHeight * pixelHeight;
	float squareImageHeight = imageHeight * imageHeight;
	return squarePixelHeight / squareImageHeight * (MAX_FREQ - MIN_FREQ) + MIN_FREQ;
}

static float LogarithmicHeightToFreq(int pixelHeight, int imageHeight){
	float ratio = pow((float)(MAX_FREQ - MIN_FREQ), (1.0 / (float)imageHeight));
	return pow(ratio, pixelHeight) + MIN_FREQ;
}

static float HarmonicHeightToFreq(int pixelHeight, int imageHeight){
	float fundamental = MAX_FREQ / imageHeight;
	return fundamental * (pixelHeight + 1);
}

void Converter::SetScaleType(ScaleType type)
{
	ScaleSystem = type;

	switch(ScaleSystem)
    {
		case Linear:
        {
			HeightToFrequency = LinearHeightToFreq;
			break;
		}
		case Exponential:
        {
			HeightToFrequency = ExponentialHeightToFreq;
			break;
		}
        //In practice, Logarithmic scaling sounds most natural to the human ear
        //Other scaling systems are put in for future extension, but currently are unused
		case Logarithmic:
        {
			HeightToFrequency = LogarithmicHeightToFreq;
			break;
		}
		case Harmonic:
        {
			HeightToFrequency = HarmonicHeightToFreq;
			break;
		}
	}
    
    //TODO: this loop could be parallelized with a parallel map
    for(int i = 0; i < OscCount; i++)
    {
        OscBank[i]->SetFrequency(HeightToFrequency(i, Height));
    }
}
