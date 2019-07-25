#ifndef FLIPHORIZ
#define FLIPHORIZ
#include "ImageFilter.h"

using namespace juce;

class FlipHorizFilter: public ImageFilter {
public:
	FlipHorizFilter() {};
	virtual ~FlipHorizFilter(){};
	void Process(Image*);
};

#endif
