#include "AudioTransportComponent.h"
#include "ImageTransComponent.h"
#include "ImageDisplayComponent.h"
#include "../Backend/Converter.h"

AudioTransportComponent::AudioTransportComponent (ImageTransComponent* itc, ImageDisplayComponent* idc, Converter* converter)
{
    //Audio Transport Component handles GUI events for playing and pausing Audio; it includes the play button and auto-scan slider
    imgTraComp = itc;
    imgDisComp = idc;
    ImageConverter = converter;
    addAndMakeVisible (ScanSpeedComponent);
    ScanSpeedComponent.setRange (-128, 128, 1);
    ScanSpeedComponent.setSliderStyle (Slider::LinearHorizontal);
    ScanSpeedComponent.setTextBoxStyle (Slider::TextBoxLeft, false, 50, 80);
    ScanSpeedComponent.setEnabled(false);
    ScanSpeedComponent.onValueChange = [this]
    {
        //Updates the auto-scan speed of the image's column slider value
        if((int)ScanSpeedComponent.getValue() == 0){
          imgDisComp->showSlider();
        } else {
          imgDisComp->hideSlider();
        }
        SetScanSpeed((int)ScanSpeedComponent.getValue());
    };

    addAndMakeVisible (SpeedLabel);
    SpeedLabel.setText(TRANS("Pixels Per Second:"), NotificationType::dontSendNotification);

    addAndMakeVisible (PlayPauseButton);
    PlayPauseButton.setButtonText (TRANS("Play"));
    PlayPauseButton.setColour (TextButton::buttonColourId, Colour (0xff30ff30));
    PlayPauseButton.setColour (TextButton::textColourOnId, Colours::black);
    PlayPauseButton.setEnabled(false);
    PlayPauseButton.onClick = [this]
    {
        //Toggles Play/Pause Button
        if(is_playing)
        {
            PlayPauseButton.setButtonText (TRANS("Play"));
            PlayPauseButton.setColour (TextButton::buttonColourId, Colour (0xff30ff30));
            imgTraComp->enableButtons();
        }
        else
        {
            PlayPauseButton.setButtonText (TRANS("Pause"));
            PlayPauseButton.setColour (TextButton::buttonColourId, Colour (0xffff3030));
            imgTraComp->disableButtons();
        }
        is_playing = !is_playing;
        ImageConverter->IsPlaying = is_playing;
    };

    setSize (600, 400);

}

void AudioTransportComponent::SetScanSpeed(int pixelsPerSecond)
{
    // Hides the slider if the PixelsPerSecond is not set to zero
    if(pixelsPerSecond == 0)
    {
        ShouldAutoScan = false;
        return;
    }
    else
    {
        ShouldAutoScan = true;
        ColumnDelta = (float) pixelsPerSecond / 44100.0f;
    }
}

AudioTransportComponent::~AudioTransportComponent()
{
}

void AudioTransportComponent::enableTrans(){
    PlayPauseButton.setEnabled(true);
    ScanSpeedComponent.setEnabled(true);
}

void AudioTransportComponent::paint (Graphics& g)
{
    g.fillAll (Colour (0xff505050));
}

void AudioTransportComponent::resized()
{
    SpeedLabel.setBounds(proportionOfWidth(0.01f), proportionOfHeight (0.1f), proportionOfWidth(0.29f), proportionOfHeight(0.85f));
    ScanSpeedComponent.setBounds(proportionOfWidth(0.31f), proportionOfHeight (0.1f), proportionOfWidth(0.39f), proportionOfHeight(0.85f));
    PlayPauseButton.setBounds (proportionOfWidth (0.71f), proportionOfHeight (0.1f), proportionOfWidth (0.28f), proportionOfHeight (0.85f));
}


void AudioTransportComponent::forceStop(){
    PlayPauseButton.setButtonText (TRANS("Play"));
    PlayPauseButton.setColour (TextButton::buttonColourId, Colour (0xff30ff30));
    imgTraComp->enableButtons();
    is_playing = false;
    ImageConverter->IsPlaying = false;
}

#if 0
#endif
