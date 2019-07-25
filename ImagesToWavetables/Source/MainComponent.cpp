
#include "MainComponent.h"
#include "../UI Components/ImageDisplayComponent.h"
#include "../UI Components/SlidersBoxComponent.h"
#include "../UI Components/ImageTransComponent.h"
#include "../UI Components/FileIOComponent.h"
#include "../UI Components/AudioTransportComponent.h"

MainComponent::MainComponent()
{
    setAudioChannels (0, 2);
    ImageConverter = new Converter();

#pragma region UISETUP
    TaskbarIcon = new SystemTrayIconComponent();
    TaskbarIcon->setIconTooltip("Images2Wavetables");
    DisplayArea = new ImageDisplayComponent(NULL, ImageConverter);
    SliderArea = new SlidersBoxComponent(ImageConverter);
    TransArea = new ImageTransComponent(DisplayArea);
    AudioTransArea = new AudioTransportComponent(TransArea, DisplayArea, ImageConverter);
    ioArea = new FileIOComponent(DisplayArea, SliderArea, TransArea, AudioTransArea);
    centreWithSize (750,400);
    addAndMakeVisible(*SliderArea);
    addAndMakeVisible(*TransArea);
    addAndMakeVisible(*DisplayArea);
    addAndMakeVisible(*AudioTransArea);
    addAndMakeVisible(*ioArea);

#pragma endregion
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    delete TaskbarIcon;
    delete DisplayArea;
    delete SliderArea;
    delete TransArea;
    delete AudioTransArea;
    delete ioArea;
    delete ImageConverter;
    shutdownAudio();
}

//==============================================================================
// Audio Processing Code
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{

}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    // Streams an audio block to the soundcard
    bufferToFill.clearActiveBufferRegion();
    
    auto* leftBuffer = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
    auto* rightBuffer = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);
    
    if(ImageConverter->IsPlaying)
    {
        for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
        {
            ImageConverter->Read(leftBuffer+sample, rightBuffer+sample);
            if(ioArea->IsRecording)
            {
                ioArea->StreamToBuffer(leftBuffer[sample], rightBuffer[sample]);
            }
            if(AudioTransArea->ShouldAutoScan)
            {
                int prevTick = Tick;
                Tick += AudioTransArea->ColumnDelta + 127.0f;
                while(Tick >= 127.0f)
                {
                    Tick -= 127.0f;
                }
                int newTick = Tick;
                if(prevTick != newTick)
                    ImageConverter->SetColumn(Tick);
            }
        }
    }
}

void MainComponent::releaseResources()
{

}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    TransArea->setBounds (proportionOfWidth (0.0f), proportionOfHeight (0.9f), proportionOfWidth (0.6f), proportionOfHeight (0.1f));
    ioArea->setBounds (proportionOfWidth (0.0f), proportionOfHeight (0.0f), proportionOfWidth (0.2f), proportionOfHeight (0.1f));
    AudioTransArea->setBounds(proportionOfWidth (0.2f), proportionOfHeight (0.0f), proportionOfWidth (0.4f), proportionOfHeight (0.1f));
    DisplayArea->setBounds (proportionOfWidth (0.0f), proportionOfHeight (0.1f), proportionOfWidth (0.6f), proportionOfHeight (0.8f));
    SliderArea->setBounds (proportionOfWidth (0.6f), proportionOfHeight (0.0f), proportionOfWidth (0.4f), proportionOfHeight (1.0f));
}
