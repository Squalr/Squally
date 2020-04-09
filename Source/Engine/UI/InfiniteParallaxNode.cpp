#include "InfiniteParallaxNode.h"

#include "cocos/2d/CCNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/renderer/CCRenderer.h"

using namespace cocos2d;

InfiniteParallaxNode* InfiniteParallaxNode::create(std::string spriteResourcePath)
{
	InfiniteParallaxNode* instance = new InfiniteParallaxNode(spriteResourcePath);

	instance->autorelease();

	return instance;
}

InfiniteParallaxNode::InfiniteParallaxNode(std::string spriteResourcePath)
{
	this->spriteScale = this->getScale();
	this->spriteAnchor = Vec2(0.5f, 0.5f);
	this->nodes = std::vector<Node*>();
	this->resourcePath = spriteResourcePath;

	this->rebuildNodes();
}

InfiniteParallaxNode::~InfiniteParallaxNode()
{
}

void InfiniteParallaxNode::setScale(float scale)
{
	this->spriteScale = scale;
	this->rebuildNodes();
}

void InfiniteParallaxNode::setAnchorPoint(const Vec2& anchor)
{
	this->spriteAnchor = anchor;

	for (auto next : this->nodes)
	{
		next->setAnchorPoint(this->spriteAnchor);
	}
}

void InfiniteParallaxNode::rebuildNodes()
{
	for (auto next : this->nodes)
	{
		this->removeChild(next, true);
	}

	this->nodes.clear();

	const int overlap = 0;

	Sprite* nextSprite = Sprite::create(this->resourcePath);
	nextSprite->setScale(this->spriteScale);
	this->spriteWidth = nextSprite->getContentSize().width * this->spriteScale;
	float remainingSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize().width * 4.0f;

	Vec2 nextPosition = Vec2(-this->spriteWidth, 0.0f);

	if (this->spriteWidth > 0)
	{
		do
		{
			nextSprite->setPosition(nextPosition);

			this->nodes.push_back(nextSprite);
			this->addChild(nextSprite, 0, Vec2(1.0f, 1.0f), nextPosition);

			remainingSize -= this->spriteWidth;

			if (remainingSize > 0.0f)
			{
				nextSprite = Sprite::create(this->resourcePath);
				nextSprite->setScale(this->spriteScale);
				nextPosition.x += this->spriteWidth - overlap;
			}

		} while (remainingSize > 0.0f);
	}

	// Anchor all new nodes
	this->setAnchorPoint(this->spriteAnchor);
}

void InfiniteParallaxNode::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
	Vec2 position = this->getParent()->convertToWorldSpace(this->getPosition());

	if (position.x < -this->spriteWidth)
	{
		this->setPosition(Vec2(0, this->getPosition().y));
	}

	if (position.x > this->spriteWidth)
	{
		this->setPosition(Vec2(0, this->getPosition().y));
	}

	ParallaxNode::visit(renderer, parentTransform, parentFlags);
}
