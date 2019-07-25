
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "../Backend/Converter.h"

class SlidersBoxComponent  : public Component
{
public:
    SlidersBoxComponent (Converter* converter);
    ~SlidersBoxComponent();

    void paint (Graphics& g) override;
    void resized() override;
    void enableSliders();
    void disableSliders();

private:
    Slider rPanSlider;
    Slider rVolSlider;
    Slider gPanSlider;
    Slider gVolSlider;
    Slider bPanSlider;
    Slider bVolSlider;
    Converter* ImageConverter;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SlidersBoxComponent)
};
