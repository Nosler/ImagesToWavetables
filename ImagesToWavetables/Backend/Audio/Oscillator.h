#ifndef OSCILLATOR
#define OSCILLATOR

enum OscillatorType {
	Sine,
	Square,
	Saw,
	Triangle
};

class Oscillator{
public:
    float Position;
	Oscillator(float freq, float amp, float sampleRate, int tableSize);
	~Oscillator();
    void SetSampleRate(int sampleRate);
	void SetFrequency(float freq);
	void SetAmplitude(float amp);
	void SetOscillatorType(OscillatorType type);
	float Read();
private:
	OscillatorType OscType;
	float* Wavetable;
	int TableSize;
	float SampleRate;
	float Frequency;
	float Amplitude;
	float Delta;
	float At(float index);
};

#endif
