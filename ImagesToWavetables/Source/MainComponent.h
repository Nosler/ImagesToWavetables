#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "../Backend/Converter.h"
#include "../UI Components/ImageDisplayComponent.h"
#include "../UI Components/SlidersBoxComponent.h"
#include "../UI Components/ImageTransComponent.h"
#include "../UI Components/FileIOComponent.h"
#include "../UI Components/AudioTransportComponent.h"

class MainComponent   : public AudioAppComponent
{
public:
    int TickThreshold;
    MainComponent();
    ~MainComponent();
    
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    
    void paint (Graphics& g) override;
    void resized() override;
    
private:
    SlidersBoxComponent* SliderArea;
    FileIOComponent* ioArea;
    ImageTransComponent* TransArea;
    ImageDisplayComponent* DisplayArea;
    AudioTransportComponent* AudioTransArea;
    TextButton* OpenButton;
    SystemTrayIconComponent* TaskbarIcon;
    Image ImageToConvert;
    Converter* ImageConverter;
    
    float Tick;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
