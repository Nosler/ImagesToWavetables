#ifndef FLIPVERT
#define FLIPVERT
#include "ImageFilter.h"

using namespace juce;

class FlipVertFilter: public ImageFilter {
public:
	FlipVertFilter() {};
    virtual ~FlipVertFilter() {};
	virtual void Process(Image*);
};

#endif
