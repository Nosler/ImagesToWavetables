#ifndef IMAGEFILTER
#define IMAGEFILTER

#include "JuceHeader.h"

using namespace juce;

class ImageFilter{
public:
    // Modify the image pointer in place
    virtual ~ImageFilter() {};
	virtual void Process(Image*) = 0;
};

#endif
