#include "RotateLeftFilter.h"

using namespace juce;

void RotateLeftFilter::Process(Image* input) {
    // Getting height and width for processing
	int x = input->getWidth();
	int y = input->getHeight();

	// Creating temp image, swapped height and width
	Image* tempImg = new Image(input->getFormat(), y, x, false);

	// Rotate by 90 deg
	for (int ix = 0; ix < x; ix++) {
		for (int iy = 0; iy < y; iy++) {
			tempImg->setPixelAt(iy, x - ix, input->getPixelAt(ix, iy));
		}
	}

	*input = *tempImg;
    delete tempImg;
}
