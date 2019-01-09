#include "MathUtils.h"

#include <algorithm>

bool MathUtils::fuzzyEquals(float a, float b, float var)
{ 
	return a - var <= b && a + var >= b;
}


float MathUtils::clamp(float n, float lower, float upper)
{
	return std::max(lower, std::min(n, upper));
}

int MathUtils::clamp(int n, int lower, int upper)
{
	return std::max(lower, std::min(n, upper));
}

float MathUtils::wrappingNormalize(float value, float start, float end)
{
	double width = end - start;
	double offsetValue = value - start;

	return (offsetValue - (std::floor(offsetValue / width) * width)) + start;
}

int MathUtils::wrappingNormalize(int value, int start, int end)
{
	int width = end - start;
	int offsetValue = value - start;

	return (offsetValue - ((offsetValue / width) * width)) + start;
}
