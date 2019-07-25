#ifndef ROTATERFILTER
#define ROTATERFILTER
#include "ImageFilter.h"

using namespace juce;

class RotateRightFilter: public ImageFilter {
public:
	RotateRightFilter() {};
    virtual ~RotateRightFilter() {};
	virtual void Process(Image*);
};

#endif
