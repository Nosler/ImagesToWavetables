#include "FileIOComponent.h"
#include "../Source/MainComponent.h"
#include "ImageDisplayComponent.h"
#include "ImageTransComponent.h"
#include "SlidersBoxComponent.h"
#include "AudioTransportComponent.h"

FileIOComponent::FileIOComponent (ImageDisplayComponent* idc, SlidersBoxComponent* sbc, ImageTransComponent* itc, AudioTransportComponent* atc)
{
    imgDisComp = idc;
    sliBoxComp = sbc;
    imgTraComp = itc;
    audTraComp = atc;

    AudioOutBuffer = new std::list<float>[2]; //Re-sizable Stereo Audio Buffer for streaming to disk

    addAndMakeVisible (SaveAudioButton);
    SaveAudioButton.setButtonText (TRANS("Record"));
    SaveAudioButton.setColour (TextButton::buttonColourId, Colour (0xff565656));
    SaveAudioButton.setColour (TextButton::textColourOnId, Colours::black);
    SaveAudioButton.setEnabled(false);
    SaveAudioButton.onClick = [this]
    {
        // Toggle IsRecording
        IsRecording = !IsRecording;
        if(!IsRecording){
            //If "Record" was selected, temporarily stop the audio stream
            audTraComp->forceStop();
            SaveAudioButton.setColour (TextButton::textColourOffId, Colour (0xffffffff));
            SaveAudioButton.setColour (TextButton::buttonColourId, Colour (0xff565656));
            SaveAudioButton.setButtonText (TRANS("Record"));
            FileChooser fileDialog ("Save .wav", (File::getSpecialLocation(File::userHomeDirectory)).getChildFile("Untitled.wav"), "*.wav", false);
            if(fileDialog.browseForFileToSave(true))
            {
                // Pipe audio data to a file
                File outputFile = fileDialog.getResult();
                int size = (int)AudioOutBuffer[0].size();
                AudioSampleBuffer* buffer = new AudioSampleBuffer(2,size);

                buffer->clear();

                CopyAudioToBuffer(buffer);

                WavAudioFormat* WavFile = new WavAudioFormat();

                FileOutputStream* outputStream = outputFile.createOutputStream();

                AudioFormatWriter* streamWriter = WavFile->createWriterFor(outputStream, 44100, 2, 16, NULL, 0);

                streamWriter->writeFromAudioSampleBuffer(*buffer, 0, size);

                delete streamWriter;
                delete buffer;
            }
        }
        else
        {
            //Begins a new audio recording, clearing the existing recorded audio
            ClearAudioBuffer();
            SaveAudioButton.setColour (TextButton::textColourOffId, Colour (0xffe30000));
            SaveAudioButton.setColour (TextButton::buttonColourId, Colour (0xff754c4c));
            SaveAudioButton.setButtonText (TRANS("Recording"));
        }
    };

    addAndMakeVisible (OpenImageButton);
    OpenImageButton.setButtonText (TRANS("Open"));
    OpenImageButton.setColour (TextButton::buttonColourId, Colour (0xff565656));
    OpenImageButton.onClick = [this]
    {
      // Opens a modal file dialog box for selecting an Image
        if(!dialog_open){
            FileChooser fileDialog ("Please select an image you want to convert...", File::getSpecialLocation (File::userHomeDirectory), "*.png;*.jpeg;*.jpg", false);
            dialog_open = true;
            if(fileDialog.browseForFileToOpen()){
                audTraComp->forceStop();
                File file_path (fileDialog.getResult());
                if(file_path.getSize() > 16){
                    Image* image = new Image();
                    *image = ImageCache::getFromFile(file_path).rescaled(128, 128);
                    imgDisComp->updateImage(image);
                    SaveAudioButton.setEnabled(true);
                    imgTraComp->enableButtons();
                    sliBoxComp->enableSliders();
                    audTraComp->enableTrans();
                }
            }
            dialog_open = false;
        }
    };
    setSize (200, 100);
}

void FileIOComponent::CopyAudioToBuffer(juce::AudioSampleBuffer *buffer)
{
    float* leftChannel = buffer->getWritePointer (0);
    float* rightChannel = buffer->getWritePointer(1);

    int j = 0;
    for(auto i = AudioOutBuffer[0].begin(); i != AudioOutBuffer[0].end(); i++)
    {
        leftChannel[j++] = *i;
    }
    j = 0;
    for(auto i = AudioOutBuffer[1].begin(); i != AudioOutBuffer[1].end(); i++)
    {
        rightChannel[j++] = *i;
    }
}

void FileIOComponent::StreamToBuffer(float leftSignal, float rightSignal)
{
    AudioOutBuffer[0].push_back(leftSignal);
    AudioOutBuffer[1].push_back(rightSignal);
}

void FileIOComponent::ClearAudioBuffer()
{
    AudioOutBuffer[0].clear();
    AudioOutBuffer[1].clear();
}
FileIOComponent::~FileIOComponent()
{
    delete[] AudioOutBuffer;
}

void FileIOComponent::paint (Graphics& g)
{
    g.fillAll (Colour (0xff505050));
}

void FileIOComponent::resized()
{
    OpenImageButton.setBounds(proportionOfWidth(0.02f), proportionOfHeight (0.1f), proportionOfWidth(0.4f), proportionOfHeight(0.85f));
    SaveAudioButton.setBounds (proportionOfWidth (0.44f), proportionOfHeight (0.1f), proportionOfWidth (0.54f), proportionOfHeight (0.85f));
}

#if 0

#endif
