#pragma once

#include "ImageDisplayComponent.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "../Backend/Visual/FlipHorizFilter.h"
#include "../Backend/Visual/FlipVertFilter.h"
#include "../Backend/Visual/RotateLeftFilter.h"
#include "../Backend/Visual/RotateRightFilter.h"
#include "../Backend/Visual/HSLFilter.h"

class ImageTransComponent  : public Component
{
public:
    ImageTransComponent (ImageDisplayComponent* idc);
    ~ImageTransComponent();

    void paint (Graphics& g) override;
    void resized() override;
    void enableButtons();
    void disableButtons();

private:
    ImageDisplayComponent* imgDisComp;
    FlipVertFilter flipVFil;
    FlipHorizFilter flipHFil;
    RotateLeftFilter rotLFil;
    RotateRightFilter rotRFil;
    HSLFilter hslFilt;
    ComboBox TransDropDown;
    TextButton ApplyFiltButton;
    TextButton FlipXButton;
    TextButton FlipYButton;
    TextButton RotateLButton;
    TextButton RotateRButton;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ImageTransComponent)
};
