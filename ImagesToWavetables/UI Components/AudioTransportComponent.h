#pragma once

#include "JuceHeader.h"
#include "ImageTransComponent.h"
#include "ImageDisplayComponent.h"
#include "../Backend/Converter.h"

class AudioTransportComponent  : public Component
{
public:
    AudioTransportComponent (ImageTransComponent* itc, ImageDisplayComponent* idc, Converter* converter);
    ~AudioTransportComponent();
    void paint (Graphics& g) override;
    void resized() override;
    void enableTrans();
    void forceStop();
    void SetScanSpeed(int pixelsPerSecond);
    
    bool ShouldAutoScan;
    float ColumnDelta;
    
private:
    Converter* ImageConverter;
    ImageDisplayComponent* imgDisComp;
    ImageTransComponent* imgTraComp;
    Label SpeedLabel;
    TextButton PlayPauseButton;
    Slider ScanSpeedComponent;
    bool is_playing = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioTransportComponent)
};
