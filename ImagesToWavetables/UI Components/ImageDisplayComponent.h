
#pragma once

#include "JuceHeader.h"
#include "../Backend/Converter.h"

class ImageDisplayComponent  : public Component
{
public:
    ImageDisplayComponent (Image* image, Converter* converter);
    ~ImageDisplayComponent();

    void paint (Graphics& g) override;
    void resized() override;
    void updateImage(Image* img);
    void Repaint(Image* image);
    Image* getImage();
    void hideSlider();
    void showSlider();
private:
    int Column;
    Slider ColumnSlider;
    ImageComponent ImageBoard;
    Image* Img = nullptr;
    Converter* AudioConverter;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ImageDisplayComponent)
};
