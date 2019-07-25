#ifndef INTERPOLATIONUTILS
#define INTERPOLATIONUTILS

#include <math.h>

namespace InterpolationUtils
{
	static double Lerp(double a, double b, double fract)
	{
		return a + fract * (b - a);
	}

	static double Sinterp(double a, double b, double fract)
	{
		return a * cos(fract * M_PI / 2.0) + b * sin(fract * M_PI / 2.0);
	}
}

#endif
