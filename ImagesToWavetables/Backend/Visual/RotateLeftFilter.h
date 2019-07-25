#ifndef ROTATELFILTER
#define ROTATELFILTER
#include "ImageFilter.h"

using namespace juce;

class RotateLeftFilter: public ImageFilter {
public:
	RotateLeftFilter() {};
    virtual ~RotateLeftFilter() {};
	virtual void Process(Image*);
};

#endif
