#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class MathUtils
{
public:
	static float clamp(float n, float lower, float upper);
	static int clamp(int n, int lower, int upper);
};

