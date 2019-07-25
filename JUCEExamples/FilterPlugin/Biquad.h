#ifndef _BIQUAD_
#define _BIQUAD_

enum FilterType {
    lowpass = 0,
    highpass,
    bandpass,
    notch,
    peak,
    lowshelf,
    highshelf
};

class Biquad {
public:
    Biquad();
    Biquad(int type, int sr, double cutoff, double Q, double peakGainDB);
    ~Biquad();
    void setType(int type);
    void setQ(double Q);
    void setCutoff(double cutoff);
    void setPeakGain(double peakGainDB);
    void setBiquad(int type, double cutoff, double Q, double peakGain);
    double process(double in);
    
private:
    void calcBiquad();

    int type, sampleRate;
    double a0, a1, a2, b1, b2;
    double Fc, Q, peakGain;
    double z1, z2;
};

#endif
