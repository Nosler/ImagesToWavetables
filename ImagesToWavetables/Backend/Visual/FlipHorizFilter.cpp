#include "FlipHorizFilter.h"

using namespace juce;

void FlipHorizFilter::Process(Image* input) {
	// Getting height and width for processing
	int x = input->getWidth();
	int y = input->getHeight();
    
	// Creating temp image
    Image* tempImg = new Image(input->getFormat(), x, y, false);

	// Flipping pixels horizontally
	for (int ix = 0; ix <= x; ix++) {
		for (int iy = 0; iy <= y; iy++) {
			tempImg->setPixelAt(ix, iy, input->getPixelAt(x - ix, iy));
		}
	}
    
    *input = *tempImg;
    delete tempImg;
}
