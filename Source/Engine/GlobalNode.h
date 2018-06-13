#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class GlobalNode : public Node
{
public:
	virtual void initializeEventListeners() = 0;
};
