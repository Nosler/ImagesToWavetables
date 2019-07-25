
#include "SlidersBoxComponent.h"
#include "../Backend/Converter.h"

SlidersBoxComponent::SlidersBoxComponent (Converter* converter)
{
  // Create all the components
    ImageConverter = converter;
    setName ("SlidersArea");
    addAndMakeVisible (rPanSlider);
    rPanSlider.setRange (-1, 1, 0.01);
    rPanSlider.setSliderStyle (Slider::Rotary);
    rPanSlider.setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    rPanSlider.setColour (Slider::thumbColourId, Colours::red);
    rPanSlider.setColour (Slider::rotarySliderFillColourId, Colour(0xff5b0000));
    rPanSlider.setEnabled(false);
    rPanSlider.onValueChange = [this]
    {
        float value = (rPanSlider.getValue() + 1.0f) * 0.5f;
        ImageConverter->UpdatePan(0, value);
    };

    addAndMakeVisible (rVolSlider);
    rVolSlider.setRange (0, 1.0, 0.001);
    rVolSlider.setSliderStyle (Slider::LinearVertical);
    rVolSlider.setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    rVolSlider.setColour (Slider::thumbColourId, Colours::red);
    rVolSlider.setColour (Slider::trackColourId, Colour(0xff5b0000));
    rVolSlider.setEnabled(false);
    rVolSlider.setValue(0.5);
    rVolSlider.onValueChange = [this]
    {
        ImageConverter->UpdateLevel(0, rVolSlider.getValue());
    };

    addAndMakeVisible (gPanSlider);
    gPanSlider.setRange (-1, 1, 0.01);
    gPanSlider.setSliderStyle (Slider::Rotary);
    gPanSlider.setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    gPanSlider.setColour (Slider::thumbColourId, Colours::lime);
    gPanSlider.setColour (Slider::rotarySliderFillColourId, Colour(0xff005b00));
    gPanSlider.setEnabled(false);
    gPanSlider.onValueChange = [this]
    {
        float value = (gPanSlider.getValue() + 1.0f) * 0.5f;
        ImageConverter->UpdatePan(1, value);
    };

    addAndMakeVisible (gVolSlider);
    gVolSlider.setRange (0, 1.0, 0.001);
    gVolSlider.setSliderStyle (Slider::LinearVertical);
    gVolSlider.setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    gVolSlider.setColour (Slider::thumbColourId, Colours::lime);
    gVolSlider.setColour (Slider::trackColourId, Colour(0xff005b00));
    gVolSlider.setEnabled(false);
    gVolSlider.setValue(0.5);
    gVolSlider.onValueChange = [this]
    {
        ImageConverter->UpdateLevel(1, gVolSlider.getValue());
    };

    addAndMakeVisible (bPanSlider);
    bPanSlider.setRange (-1.0, 1.0, 0.01);
    bPanSlider.setSliderStyle (Slider::Rotary);
    bPanSlider.setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    bPanSlider.setColour (Slider::thumbColourId, Colours::blue);
    bPanSlider.setColour (Slider::rotarySliderFillColourId, Colour(0xff00005b));
    bPanSlider.setEnabled(false);
    bPanSlider.onValueChange = [this]
    {
        float value = (bPanSlider.getValue() + 1.0f) * 0.5f;
        ImageConverter->UpdatePan(2, value);
    };

    addAndMakeVisible (bVolSlider);
    bVolSlider.setRange (0, 1.0, 0.001);
    bVolSlider.setSliderStyle (Slider::LinearVertical);
    bVolSlider.setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    bVolSlider.setColour (Slider::thumbColourId, Colours::blue);
    bVolSlider.setColour (Slider::trackColourId, Colour(0xff00005b));
    bVolSlider.setEnabled(false);
    bVolSlider.setValue(0.5);
    bVolSlider.onValueChange = [this]
    {
        ImageConverter->UpdateLevel(2, bVolSlider.getValue());
    };

    setSize (300, 300);
}

SlidersBoxComponent::~SlidersBoxComponent()
{
}

void SlidersBoxComponent::paint (Graphics& g)
{
    g.fillAll (Colour (0xff505050));
}

void SlidersBoxComponent::resized()
{
    rPanSlider.setBounds (proportionOfWidth (0.0f), proportionOfHeight (0.6604f), proportionOfWidth (0.3303f), proportionOfHeight (0.3309f));
    rVolSlider.setBounds (proportionOfWidth (0.0f), proportionOfHeight (0.0f), proportionOfWidth (0.3303f), proportionOfHeight (0.6604f));
    gPanSlider.setBounds (proportionOfWidth (0.3303f), proportionOfHeight (0.6604f), proportionOfWidth (0.3303f), proportionOfHeight (0.3309f));
    gVolSlider.setBounds (proportionOfWidth (0.3303f), proportionOfHeight (0.0f), proportionOfWidth (0.3303f), proportionOfHeight (0.6604f));
    bPanSlider.setBounds (proportionOfWidth (0.6605f), proportionOfHeight (0.6604f), proportionOfWidth (0.3303f), proportionOfHeight (0.3309f));
    bVolSlider.setBounds (proportionOfWidth (0.6605f), proportionOfHeight (0.0f), proportionOfWidth (0.3303f), proportionOfHeight (0.6604f));
}

void SlidersBoxComponent::enableSliders(){
    rPanSlider.setEnabled(true);
    rVolSlider.setEnabled(true);
    gPanSlider.setEnabled(true);
    gVolSlider.setEnabled(true);
    bPanSlider.setEnabled(true);
    bVolSlider.setEnabled(true);
}

void SlidersBoxComponent::disableSliders(){
    rPanSlider.setEnabled(false);
    rVolSlider.setEnabled(false);
    gPanSlider.setEnabled(false);
    gVolSlider.setEnabled(false);
    bPanSlider.setEnabled(false);
    bVolSlider.setEnabled(false);
}

#if 0

#endif
