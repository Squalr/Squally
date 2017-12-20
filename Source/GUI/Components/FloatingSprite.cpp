#include "FloatingSprite.h"

FloatingSprite* FloatingSprite::create(std::string spriteResourcePath)
{
	FloatingSprite* node = new FloatingSprite(spriteResourcePath);

	node->autorelease();

	return node;
}

FloatingSprite::FloatingSprite(std::string spriteResourcePath)
{
	this->nodeA = Sprite::create(spriteResourcePath);

	this->scheduleUpdate();
}

FloatingSprite::~FloatingSprite()
{
}

void FloatingSprite::update(float dt)
{
	if (this->getPosition().x < -(this->nodeA->getContentSize().width))
	{
		this->setPosition(Vec2(0, this->getPosition().y));
	}
}
