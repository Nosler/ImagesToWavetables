#ifndef CONVERTER
#define CONVERTER

#include "Audio/Oscillator.h"
#include <JuceHeader.h>
#include <math.h>

// Defines the range of human hearing
// Do Not Modify
#define MAX_FREQ 22000.0f
#define MIN_FREQ 20.0f

using namespace juce;

enum ScaleType {
	// Determines spacing of oscillators in the frequency spectrum
	Linear,
	Exponential,
	Logarithmic,
	Harmonic
};

class Converter{
public:
    bool IsPlaying;
	Converter();
	~Converter();
    void Convert(Image* image);
	void SetOscillatorType(OscillatorType type);
    void UpdatePan(int color, float pan);
    void UpdateLevel(int color, float value);
    void SetColumn(int column);
	void SetScaleType(ScaleType type);
    void SetSampleRate(int sampleRate);
    void Reset();
    void Read(float* leftChannel, float* rightChannel);
private:
    Colour* ColumnData;
    int Column;
    double RedPan, GreenPan, BluePan;
    double RedLevel, GreenLevel, BlueLevel;
    Image* Picture;
    float InverseHeight;
    int Width, Height;
	int OscCount = 0;
	float (*HeightToFrequency)(int, int);
	ScaleType ScaleSystem;
	int OscBufferSize = 32; // Size of each Oscillator's wavetable; Must be a power of 2
	Oscillator** OscBank;
    
    // Panning Ratios
    float RatioRedLeft, RatioGreenLeft, RatioBlueLeft;
    float RatioRedRight, RatioGreenRight, RatioBlueRight;
};

#endif
