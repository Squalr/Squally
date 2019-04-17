#include "MathUtils.h"

#include <algorithm>
#include <cmath>

bool MathUtils::fuzzyEquals(float a, float b, float var)
{ 
	return a - var <= b && a + var >= b;
}


float MathUtils::clamp(float n, float lower, float upper)
{
	if (std::isnan(n) || !std::isfinite(n))
	{
		return lower;
	}
	
	return std::max(lower, std::min(n, upper));
}

int MathUtils::clamp(int n, int lower, int upper)
{
	return std::max(lower, std::min(n, upper));
}

float MathUtils::wrappingNormalize(float value, float start, float end)
{
	float size = end - start;
	float offsetValue = value - start;

	if (size == 0.0f)
	{
		return 0.0f;
	}

	return (offsetValue - (std::floor(offsetValue / size) * size)) + start;
}

int MathUtils::wrappingNormalize(int value, int start, int end)
{
	int size = end - start + 1;

    if (value < start)
	{
        value += size * ((start - value) / size + 1);
	}

    return start + (value - start) % size;
}
