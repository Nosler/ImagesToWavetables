#include "HSLFilter.h"

using namespace juce;

void HSLFilter::Process(Image* input) {
	// These are needed to iterate over the iamge
	int width = input->getWidth();
	int height = input->getHeight();
	// The original color that we will apply the hue, saturation,
	// and light (brightness) to
	Colour color;
    Image* tempImg = new Image(input->getFormat(), width, height, false);
    
	int i, j;
	for(i=0; i<width; i++) {
		for(j=0; j<height; j++) {
			// Get the color...
			color = input->getPixelAt(i,j);

			// ...apply the filter...
			color = color.withHue(color.getHue() + this->hue);
			color = color.withSaturation(color.getSaturation() + this->saturation);
			color = color.withBrightness(color.getBrightness() + this->light);

			// ...edit the image with the filter applied to each pixel.
			tempImg->setPixelAt(i, j, color);
		}
        
	}
    *input = *tempImg;
    delete tempImg;
}

void HSLFilter::updateH(float value) {
    this->hue = value;
}

void HSLFilter::updateS(float value) {
    this->saturation = value;
}

void HSLFilter::updateL(float value) {
    this->light = value;
}
