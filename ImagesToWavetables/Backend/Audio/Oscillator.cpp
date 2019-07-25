#include "Oscillator.h"
#include "../Utils/InterpolationUtils.h"
#include <math.h>

using namespace InterpolationUtils;

Oscillator::Oscillator(float freq, float amp, float sampleRate, int tableSize)
{
    Position = 0;
	TableSize = tableSize;
	Wavetable = new float[TableSize];
    SampleRate = (int)sampleRate;
    Amplitude = amp;
    SetOscillatorType(Sine);
	SetFrequency(freq);
}

void Oscillator::SetSampleRate(int sampleRate){
    // Sets the sample-rate of the oscillator, re-calculates the sample advancement delta
    SampleRate = sampleRate;
    SetFrequency(Frequency);
}

void Oscillator::SetOscillatorType(OscillatorType type){
    // if the oscillator type is unchanged, early-out
	OscType = type;

    // otherwise, assign the wavetable to the correct shape
	switch(OscType){
		case Sine:
        {
            // sinusoidal waveform
            for(int i = 0; i < TableSize; i++)
				Wavetable[i] = sin(2.0 * M_PI * (float)i / (float)TableSize);
			break;
		}
        //Presently, other waveforms are unused, but I've put them here for future extension
		case Square:
        {
            // Piecewise square waveform
			for(int i = 0; i < TableSize; i++){
				if(i < TableSize >> 1)
					Wavetable[i] = 1.0;
				else
					Wavetable[i] = 0.0;
			}
			break;
		}
		case Saw:
        {
            // Sawtooth waveform - characterized by repeating linear ramp
			for(int i = 0; i < TableSize; i++)
				Wavetable[i] = Lerp(1.0, -1.0, (float)i / TableSize);
			break;
		}
		case Triangle:
        {
			for(int i = 0; i < TableSize >> 2; i++)
			{
                // Piecewise triangle waveform
				Wavetable[i] = Lerp(0.0, 1.0, (float)i / (TableSize >> 2));
				Wavetable[i+(TableSize >> 2)] = Lerp(1.0, 0.0, (float)i / (TableSize >> 2));
				Wavetable[i+(TableSize * 2 >> 2)] = Lerp(0.0, -1.0, (float)i / (TableSize >> 2));
				Wavetable[i+(TableSize * 3 >> 2)] = Lerp(-1.0, 0.0, (float)i / (TableSize >> 2));
			}
			break;
		}
	}
}

void Oscillator::SetAmplitude(float amplitude)
{
	Amplitude = amplitude;
}

void Oscillator::SetFrequency(float freq)
{
    // Sets the frequency of the oscillator, implicitly setting the sample-advancement delta
	Frequency = freq;
	Delta = Frequency * (float) TableSize / (float) SampleRate;
}

Oscillator::~Oscillator()
{
    delete Wavetable;
}

float Oscillator::Read()
{
    // returns the newest displacement value from the oscillator
    float output = Amplitude * At(Position);
    // implicitly resets the position to avoid buffer overflow
    Position += Delta;
    while(Position > TableSize)
        Position -= TableSize;
    
    return output;
}

float Oscillator::At(float position)
{
    // internal function for linearly-interpolated buffer access
	double fract = position - (int) position;
	return Lerp(Wavetable[(int)position], Wavetable[(int)(position + 1) % TableSize], fract);
}
