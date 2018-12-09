#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class Bootstrapper 
{
public:
	static void initialize();
	static void shutDown();
};
