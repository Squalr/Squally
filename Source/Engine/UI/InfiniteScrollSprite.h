#pragma once
#include <string>
#include <vector>

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Node;
	class Renderer;
}

class InfiniteScrollSprite : public SmartNode
{
public:
	static InfiniteScrollSprite* create(std::string spriteResourcePath);

	virtual void setScale(float scale) override;
	virtual void setAnchorPoint(const cocos2d::Vec2& anchor) override;

protected:
	InfiniteScrollSprite(std::string spriteResourcePath);
	virtual ~InfiniteScrollSprite();

	void onEnter() override;
	void update(float dt) override;
	void rebuildNodes();

private:
	typedef SmartNode super;

	std::vector<cocos2d::Node*> nodes;
	float spriteWidth = 0.0f;
	float spriteScale = 0.0f;
	cocos2d::Vec2 spriteAnchor;
	std::string resourcePath;
};