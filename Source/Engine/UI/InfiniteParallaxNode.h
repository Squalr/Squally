#pragma once
#include <string>
#include <vector>

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Node;
	class Renderer;
}

class InfiniteParallaxNode : public SmartNode
{
public:
	static InfiniteParallaxNode* create(std::string spriteResourcePath);

	virtual void setScale(float scale) override;
	virtual void setAnchorPoint(const cocos2d::Vec2& anchor) override;

protected:
	InfiniteParallaxNode(std::string spriteResourcePath);
	virtual ~InfiniteParallaxNode();

	void onEnter();
	void update(float dt);
	void rebuildNodes();

	std::vector<cocos2d::Node*> nodes;
	float spriteWidth;
	float spriteScale;
	cocos2d::Vec2 spriteAnchor;
	std::string resourcePath;
private:
	typedef SmartNode super;
};