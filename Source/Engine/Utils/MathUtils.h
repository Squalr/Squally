#pragma once

#include <string>

class MathUtils
{
public:
	static bool fuzzyEquals(float a, float b, float var);
	static float clamp(float n, float lower, float upper);
	static int clamp(int n, int lower, int upper);
	static float bound(float n, float lower, float upper);
	static int bound(int n, int lower, int upper);
	static float wrappingNormalize(float value, float start, float end);
	static int wrappingNormalize(int value, int start, int end);
	static unsigned char resolveBinaryMathExpression(const std::string& expression);
	static bool isInteger(const std::string& str);
};
