/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FilterPluginAudioProcessorEditor::FilterPluginAudioProcessorEditor (FilterPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 170);
    
    frequencyCutoff.setSliderStyle(Slider::LinearHorizontal);
    frequencyCutoff.setRange(20.0, 20000.0, 1.0);
    frequencyCutoff.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    frequencyCutoff.setPopupDisplayEnabled (true, false, this);
    frequencyCutoff.setTextValueSuffix (" Hz");
    frequencyCutoff.setValue(1.0);
    frequencyCutoff.onValueChange = [this]
        {
            for(int i = 0; i < processor.getTotalNumInputChannels(); i++)
                processor.biquadFilters[i]->setCutoff(frequencyCutoff.getValue());
        };
    addAndMakeVisible(&frequencyCutoff);
    
    qSlider.setSliderStyle(Slider::LinearHorizontal);
    qSlider.setRange(0.0, 1.0, 0.0);
    qSlider.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    qSlider.setPopupDisplayEnabled (true, false, this);
    qSlider.setTextValueSuffix (" Q");
    qSlider.setValue(1.0);
    qSlider.onValueChange = [this]
        {
            for(int i = 0; i < processor.getTotalNumInputChannels(); i++)
                processor.biquadFilters[i]->setQ(qSlider.getValue());
        };
    addAndMakeVisible(&qSlider);
    
    filterTypeBox.setEditableText(false);
    filterTypeBox.setTooltip("Filter Type");
    filterTypeBox.addItemList(
        {
            "Lowpass",
            "Highpass",
            "Bandpass",
            "Notch",
            "Peak",
            "Lowshelf",
            "Highshelf"
        },
        1
    );
    filterTypeBox.onChange = [this]
        {
            for(int i = 0; i < processor.getTotalNumInputChannels(); i++)
                processor.biquadFilters[i]->setType(filterTypeBox.getSelectedId() - 1);
        };
    addAndMakeVisible(&filterTypeBox);
}

FilterPluginAudioProcessorEditor::~FilterPluginAudioProcessorEditor()
{
}

//==============================================================================
void FilterPluginAudioProcessorEditor::sliderValueChanged (Slider* slider)
{
    
}

void FilterPluginAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::black);
    // set the current drawing colour to black
    g.setColour (Colours::white);
    // set the font size and draw text to the screen
    g.setFont (15.0f);
    g.drawFittedText ("Frequency Cutoff", 0, 0, getWidth(), 30, Justification::centred, 1);
    g.drawFittedText("Q Factor", 0, 50, getWidth(), 30, Justification::centred, 1);
    g.drawFittedText("Filter Type", 0, 100, getWidth(), 30, Justification::centred, 1);
}

void FilterPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    frequencyCutoff.setBounds(40, 30, getWidth() - 60, 20);
    qSlider.setBounds(40, 70, getWidth() - 60, 20);
    filterTypeBox.setBounds(40, 130, getWidth() - 60, 20);
}
