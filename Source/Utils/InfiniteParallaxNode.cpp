#include "InfiniteParallaxNode.h"

InfiniteParallaxNode* InfiniteParallaxNode::create()
{
	InfiniteParallaxNode* node = new InfiniteParallaxNode();

	if (node)
	{
		node->autorelease();
	}
	else
	{
		delete node;
		node = nullptr;
	}

	return node;
}

// TODO: Just put this in an update(float dt) loop
void InfiniteParallaxNode::updatePosition()
{
	if (this->getPosition().x < -_children.at(0)->getContentSize().width)
	{
		this->setPosition(Vec2(0, this->getPosition().y));
	}
}
