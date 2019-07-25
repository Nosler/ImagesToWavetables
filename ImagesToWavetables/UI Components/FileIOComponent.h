#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "ImageDisplayComponent.h"
#include "ImageTransComponent.h"
#include "SlidersBoxComponent.h"
#include "AudioTransportComponent.h"
#include <list>

class FileIOComponent  : public Component
{
public:
    FileIOComponent (ImageDisplayComponent* idc, SlidersBoxComponent* sbc, ImageTransComponent* itc, AudioTransportComponent* atc);
    ~FileIOComponent();
    void paint (Graphics& g) override;
    void resized() override;
    void getImgDispComp(ImageDisplayComponent* idc);
    bool IsRecording = false;
    void StreamToBuffer(float leftSignal, float rightSignal);
    
    void CopyAudioToBuffer(AudioSampleBuffer* buffer);
    
private:
    void ClearAudioBuffer();
    std::list<float>* AudioOutBuffer;
    TextButton SaveAudioButton;
    TextButton OpenImageButton;
    ImageDisplayComponent* imgDisComp;
    SlidersBoxComponent* sliBoxComp;
    ImageTransComponent* imgTraComp;
    AudioTransportComponent* audTraComp;
    bool dialog_open = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FileIOComponent)
};
