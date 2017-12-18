#include "InfiniteParallaxNode.h"

InfiniteParallaxNode* InfiniteParallaxNode::create()
{
	InfiniteParallaxNode* node = new InfiniteParallaxNode();

	node->autorelease();

	return node;
}

InfiniteParallaxNode::InfiniteParallaxNode()
{
	this->scheduleUpdate();
}

InfiniteParallaxNode::~InfiniteParallaxNode()
{
}

void InfiniteParallaxNode::update(float dt)
{
	if (this->getPosition().x < -_children.at(0)->getContentSize().width)
	{
		this->setPosition(Vec2(0, this->getPosition().y));
	}
}
