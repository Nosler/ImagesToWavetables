#include "FlipVertFilter.h"

using namespace juce;

void FlipVertFilter::Process(Image* input) {
	// Getting height and width for processing
	int x = input->getWidth();
	int y = input->getHeight();

    // Creating temp image
    Image* tempImg = new Image(input->getFormat(), x, y, false);

	// Flipping pixels vertically
	for (int iy = 0; iy < y; iy++) {
		for (int ix = 0; ix < x; ix++) {
			tempImg->setPixelAt(ix, iy, input->getPixelAt(ix, y - iy));
		}
	}
    
    *input = *tempImg;
    delete tempImg;
}
