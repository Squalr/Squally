#include "MathUtils.h"

#include <algorithm>

float MathUtils::clamp(float n, float lower, float upper)
{
	return std::max(lower, std::min(n, upper));
}

int MathUtils::clamp(int n, int lower, int upper)
{
	return std::max(lower, std::min(n, upper));
}
