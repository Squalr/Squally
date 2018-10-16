#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class AlgoUtils
{
public:
	static std::vector<int> subsetSum(const std::vector<int>& numbers, int sum, int requiredLength);
};

