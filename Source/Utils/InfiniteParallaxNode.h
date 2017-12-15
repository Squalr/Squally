#pragma once
#include "cocos2d.h"
#include "PointObject.h"

using namespace cocos2d;

class InfiniteParallaxNode : public ParallaxNode
{
public:
	static InfiniteParallaxNode* create();
	void updatePosition();
};