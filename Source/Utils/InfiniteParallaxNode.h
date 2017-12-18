#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class InfiniteParallaxNode : public ParallaxNode
{
public:
	static InfiniteParallaxNode* create();
	void updatePosition();

protected:
	InfiniteParallaxNode();
	~InfiniteParallaxNode();

	void update(float dt) override;
};