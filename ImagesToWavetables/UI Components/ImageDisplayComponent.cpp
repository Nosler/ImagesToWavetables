#include "ImageDisplayComponent.h"
#include "../Backend/Converter.h"

ImageDisplayComponent::ImageDisplayComponent (Image* image, Converter* converter)
{
    Img = image;
    AudioConverter = converter;
    setName ("ImageDisplay");
    addAndMakeVisible (ColumnSlider);

    if(image != NULL)
        ColumnSlider.setRange (0, image->getWidth(), 1);

    ColumnSlider.setValue(0);
    ColumnSlider.setSliderStyle (Slider::LinearHorizontal);
    ColumnSlider.setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    ColumnSlider.setAlwaysOnTop(true);
    ColumnSlider.setVisible(true);
    ColumnSlider.setEnabled(false);
    ImageBoard.toBack();
    ColumnSlider.onValueChange = [this]
    {
      // Adjusts currently playing column within the converter
        if(Img == NULL)
            return;
        AudioConverter->SetColumn((int)ColumnSlider.getValue());
        Column = ColumnSlider.getValue();
    };

    addAndMakeVisible (ImageBoard);
    setSize (300, 200);
}

ImageDisplayComponent::~ImageDisplayComponent()
{
}

void ImageDisplayComponent::paint (Graphics& g)
{
    g.fillAll (Colour (0xff000000));
    if(Img != NULL){
      g.drawImageAt(*Img, 0, 0, true);
    }
}

void ImageDisplayComponent::resized()
{
    ImageBoard.setBounds (proportionOfWidth (0.01f), proportionOfHeight (0.01f), proportionOfWidth (0.95f), proportionOfHeight (0.89f));
    ColumnSlider.setBounds (proportionOfWidth (0.15f), proportionOfHeight (0.90f), proportionOfWidth (0.67f), proportionOfHeight (0.10f));
}

void ImageDisplayComponent::updateImage(Image* img)
{
    Img = img;
    ImageBoard.setImage(*Img);
    ColumnSlider.setEnabled(true);
    ColumnSlider.setRange (0, Img->getWidth(), 1);
    AudioConverter->Convert(Img);
}

Image* ImageDisplayComponent::getImage(){
  return Img;
}

void ImageDisplayComponent::hideSlider(){
  ColumnSlider.setVisible(false);
}

void ImageDisplayComponent::showSlider(){
  ColumnSlider.setVisible(true);
}
#if 0

#endif
