/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Biquad.h"

//==============================================================================
FilterPluginAudioProcessor::FilterPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

FilterPluginAudioProcessor::~FilterPluginAudioProcessor()
{
}

//==============================================================================
const String FilterPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FilterPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FilterPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FilterPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FilterPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FilterPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FilterPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FilterPluginAudioProcessor::setCurrentProgram (int index)
{
}

const String FilterPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void FilterPluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void FilterPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    biquadFilters = new Biquad*[getTotalNumInputChannels()];
    for (int i = 0; i < getTotalNumInputChannels(); i++)
    {
        biquadFilters[i] = new Biquad(lowpass, (int)sampleRate, 2000.0, 0.5, 1.0);
    }
    
}

void FilterPluginAudioProcessor::releaseResources()
{
    for(int i = 0; i < getTotalNumInputChannels(); i++)
    {
        delete biquadFilters[i];
    }
    delete biquadFilters;
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FilterPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FilterPluginAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        
        auto* channelData = buffer.getWritePointer (channel);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            channelData[sample] = biquadFilters[channel]->process(channelData[sample]);
        }
    }
}

//==============================================================================
bool FilterPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* FilterPluginAudioProcessor::createEditor()
{
    return new FilterPluginAudioProcessorEditor (*this);
}

//==============================================================================
void FilterPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FilterPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FilterPluginAudioProcessor();
}
