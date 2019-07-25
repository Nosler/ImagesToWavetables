#include "ImageTransComponent.h"
#include "../Backend/Visual/FlipHorizFilter.h"
#include "../Backend/Visual/FlipVertFilter.h"
#include "../Backend/Visual/RotateLeftFilter.h"
#include "../Backend/Visual/RotateRightFilter.h"
#include "../Backend/Visual/HSLFilter.h"

ImageTransComponent::ImageTransComponent (ImageDisplayComponent* idc)
{
    imgDisComp = idc;
    addAndMakeVisible (TransDropDown);
    TransDropDown.setEditableText (false);
    TransDropDown.setJustificationType (Justification::centredRight);
    TransDropDown.setTextWhenNothingSelected (TRANS("Fliters"));
    TransDropDown.setTextWhenNoChoicesAvailable (TRANS("(ERR)"));
    TransDropDown.addItem (TRANS("Saturated"), 1);
    TransDropDown.addItem (TRANS("Desaturated"), 2);
    TransDropDown.addItem (TRANS("Bright"), 3);
    TransDropDown.addItem (TRANS("Dark"), 4);
    TransDropDown.addItem (TRANS("Shift Hue"), 5);
    TransDropDown.setEnabled(false);

    addAndMakeVisible (ApplyFiltButton);
    ApplyFiltButton.setButtonText (TRANS("Apply Filter"));
    ApplyFiltButton.setColour (TextButton::buttonColourId, Colour (0xff657489));
    ApplyFiltButton.setEnabled(false);
    ApplyFiltButton.onClick = [this]{
        // Apply filters based on current combobox selection
        Image* img = imgDisComp->getImage();
        switch(TransDropDown.getSelectedId())
        {
            case 1:
                // Saturated
                hslFilt.updateH(0.0f);
                hslFilt.updateS(0.2f);
                hslFilt.updateL(0.0f);
                hslFilt.Process(img);
                imgDisComp->updateImage(img);
                break;

            case 2:
                // Desaturated
                hslFilt.updateH(0.0f);
                hslFilt.updateS(-0.2f);
                hslFilt.updateL(0.0f);
                hslFilt.Process(img);
                imgDisComp->updateImage(img);
                break;

            case 3:
                // Bright
                hslFilt.updateH(0.0f);
                hslFilt.updateS(0.0f);
                hslFilt.updateL(0.20f);
                hslFilt.Process(img);
                imgDisComp->updateImage(img);
                break;

            case 4:
                // Dark
                hslFilt.updateH(0.0f);
                hslFilt.updateS(0.0f);
                hslFilt.updateL(-0.20f);
                hslFilt.Process(img);
                imgDisComp->updateImage(img);
                break;

            case 5:
                // Shift Hue
                hslFilt.updateH(0.2f);
                hslFilt.updateS(0.0f);
                hslFilt.updateL(0.0f);
                hslFilt.Process(img);
                imgDisComp->updateImage(img);
                break;
        }
    };

    addAndMakeVisible (FlipXButton);
    FlipXButton.setButtonText (TRANS("Flip X"));
    FlipXButton.setColour (TextButton::buttonColourId, Colour (0xff657489));
    FlipXButton.setEnabled(false);
    FlipXButton.onClick = [this]{
      Image* img = imgDisComp->getImage();
      flipHFil.Process(img);
      imgDisComp->updateImage(img);
    };

    addAndMakeVisible (FlipYButton);
    FlipYButton.setButtonText (TRANS("Flip Y"));
    FlipYButton.setColour (TextButton::buttonColourId, Colour (0xff657489));
    FlipYButton.setEnabled(false);
    FlipYButton.onClick = [this]{
      Image* img = imgDisComp->getImage();
      flipVFil.Process(img);
      imgDisComp->updateImage(img);
    };

    addAndMakeVisible (RotateLButton);
    RotateLButton.setButtonText (TRANS("Rotate Left"));
    RotateLButton.setColour (TextButton::buttonColourId, Colour (0xff657489));
    RotateLButton.setEnabled(false);
    RotateLButton.onClick = [this]{
      Image* img = imgDisComp->getImage();
      rotLFil.Process(img);
      imgDisComp->updateImage(img);
    };

    addAndMakeVisible (RotateRButton);
    RotateRButton.setButtonText (TRANS("Rotate Right"));
    RotateRButton.setColour (TextButton::buttonColourId, Colour (0xff657489));
    RotateRButton.setEnabled(false);
    RotateRButton.onClick = [this]{
      Image* img = imgDisComp->getImage();
      rotRFil.Process(img);
      imgDisComp->updateImage(img);
    };
    setSize (300, 20);
}

ImageTransComponent::~ImageTransComponent()
{
}

void ImageTransComponent::paint (Graphics& g)
{
    g.fillAll (Colour (0xff505050));
}

void ImageTransComponent::resized()
{
    FlipXButton.setBounds (proportionOfWidth (0.01f), proportionOfHeight (0.1f), proportionOfWidth (0.13f), proportionOfHeight (0.8f));
    FlipYButton.setBounds (proportionOfWidth (0.15f), proportionOfHeight (0.1f), proportionOfWidth (0.13f), proportionOfHeight (0.8f));
    RotateLButton.setBounds (proportionOfWidth (0.29f), proportionOfHeight (0.1f), proportionOfWidth (0.13f), proportionOfHeight (0.8f));
    RotateRButton.setBounds (proportionOfWidth (0.42f), proportionOfHeight (0.1f), proportionOfWidth (0.13f), proportionOfHeight (0.8f));
    ApplyFiltButton.setBounds (proportionOfWidth (0.60f), proportionOfHeight (0.1f), proportionOfWidth (0.15f), proportionOfHeight (0.8f));
    TransDropDown.setBounds (proportionOfWidth (0.76f), proportionOfHeight (0.1f), proportionOfWidth (0.23f), proportionOfHeight (0.8f));
}

void ImageTransComponent::enableButtons(){
    TransDropDown.setEnabled(true);
    FlipXButton.setEnabled(true);
    FlipYButton.setEnabled(true);
    RotateLButton.setEnabled(true);
    RotateRButton.setEnabled(true);
    ApplyFiltButton.setEnabled(true);
}

void ImageTransComponent::disableButtons(){
    TransDropDown.setEnabled(false);
    FlipXButton.setEnabled(false);
    FlipYButton.setEnabled(false);
    RotateLButton.setEnabled(false);
    RotateRButton.setEnabled(false);
    ApplyFiltButton.setEnabled(false);
}

#if 0  // Our little friend

#endif
