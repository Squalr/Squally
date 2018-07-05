#include "MathUtils.h"

float MathUtils::clamp(float n, float lower, float upper)
{
	return std::max(lower, std::min(n, upper));
}
