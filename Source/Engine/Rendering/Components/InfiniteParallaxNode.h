#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class InfiniteParallaxNode : public ParallaxNode
{
public:
	static InfiniteParallaxNode* create(std::string spriteResourcePath);

	virtual void setScale(float scale) override;
	virtual void setAnchorPoint(const Vec2& anchor) override;

protected:
	InfiniteParallaxNode(std::string spriteResourcePath);
	~InfiniteParallaxNode();

	void rebuildNodes();
	void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags) override;

	std::vector<Node*>* nodes;
	float spriteWidth;
	float spriteScale;
	Vec2 spriteAnchor;
	std::string resourcePath;
};