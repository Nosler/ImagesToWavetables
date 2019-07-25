#ifndef VSLFILTER
#define VSLFILTER

#include "ImageFilter.h"

using namespace juce;

class HSLFilter : public ImageFilter {
	float hue = 0.0;
	float saturation = 0.0;
	float light = 0.0;

	public:
        HSLFilter() { };
		virtual ~HSLFilter() { };
        virtual void Process(Image* input);
        
        void updateH(float value);
        void updateS(float value);
        void updateL(float value);
};

#endif
