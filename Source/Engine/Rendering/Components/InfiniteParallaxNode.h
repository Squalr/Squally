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

	void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags) override;

	std::vector<Node*>* nodes;
	float spriteWidth;
};