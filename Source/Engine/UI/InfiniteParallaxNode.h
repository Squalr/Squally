#pragma once
#include <string>
#include <vector>

#include "cocos/2d/CCParallaxNode.h"

namespace cocos2d
{
	class Node;
	class Renderer;
}

class InfiniteParallaxNode : public cocos2d::ParallaxNode
{
public:
	static InfiniteParallaxNode* create(std::string spriteResourcePath);

	virtual void setScale(float scale) override;
	virtual void setAnchorPoint(const cocos2d::Vec2& anchor) override;

protected:
	InfiniteParallaxNode(std::string spriteResourcePath);
	virtual ~InfiniteParallaxNode();

	void rebuildNodes();
	void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags) override;

	std::vector<cocos2d::Node*> nodes;
	float spriteWidth;
	float spriteScale;
	cocos2d::Vec2 spriteAnchor;
	std::string resourcePath;
private:
	typedef cocos2d::ParallaxNode super;
};