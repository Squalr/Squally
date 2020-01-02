#include "MathUtils.h"

#include <algorithm>
#include <cmath>

#include "Engine/Utils/tinyexpr.h"

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
	
	return std::max(std::min(lower, upper), std::min(n, std::max(lower, upper)));
}

int MathUtils::clamp(int n, int lower, int upper)
{
	return std::max(std::min(lower, upper), std::min(n, std::max(lower, upper)));
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

	if (size == 0)
	{
		return 0;
	}

    if (value < start)
	{
        value += size * ((start - value) / size + 1);
	}

    return start + (value - start) % size;
}

unsigned char MathUtils::resolveBinaryMathExpression(const std::string& expression)
{
	return te_interp(expression.c_str(), 0);
}

bool MathUtils::isInteger(const std::string& str)
{
   if(str.empty() || ((!isdigit(str[0])) && (str[0] != '-') && (str[0] != '+')))
   {
	   return false;
   }

   char * p;
   strtol(str.c_str(), &p, 10);

   return (*p == 0);
}
