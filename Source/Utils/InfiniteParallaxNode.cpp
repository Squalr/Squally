#include "InfiniteParallaxNode.h"

InfiniteParallaxNode* InfiniteParallaxNode::create(std::string spriteResourcePath)
{
	InfiniteParallaxNode* node = new InfiniteParallaxNode(spriteResourcePath);

	node->autorelease();

	return node;
}

InfiniteParallaxNode::InfiniteParallaxNode(std::string spriteResourcePath)
{
	this->nodeA = Sprite::create(spriteResourcePath);
	this->nodeB = Sprite::create(spriteResourcePath);

	this->addChild(this->nodeA, 0, Vec2(1.0f, 1.0f), Vec2::ZERO);
	this->addChild(this->nodeB, 0, Vec2(1.0f, 1.0f), Vec2(this->nodeB->getContentSize().width - 2, 0.0f));

	this->scheduleUpdate();
}

InfiniteParallaxNode::~InfiniteParallaxNode()
{
}

void InfiniteParallaxNode::update(float dt)
{
	if (this->getPosition().x < -(this->nodeA->getContentSize().width))
	{
		this->setPosition(Vec2(0, this->getPosition().y));
	}
}
