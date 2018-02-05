#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class InfiniteParallaxNode : public ParallaxNode
{
public:
	static InfiniteParallaxNode* create(std::string spriteResourcePath);

protected:
	InfiniteParallaxNode(std::string spriteResourcePath);
	~InfiniteParallaxNode();

	void update(float dt) override;

	std::vector<Node*>* nodes;
	float spriteWidth;
};