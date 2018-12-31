#include "FloatingSprite.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/renderer/CCTextureCache.h"

using namespace cocos2d;

FloatingSprite* FloatingSprite::create(std::string spriteResourcePath, Vec2 movement, Vec2 time)
{
	FloatingSprite* instance = new FloatingSprite(spriteResourcePath, movement, time);

	instance->autorelease();

	return instance;
}

FloatingSprite::FloatingSprite(std::string spriteResourcePath, Vec2 movement, Vec2 time)
{
	this->sprite = Sprite::create(spriteResourcePath);
	this->movement = movement;
	this->time = time;

	this->addChild(this->sprite);
}

FloatingSprite::~FloatingSprite()
{
}

void FloatingSprite::onEnter()
{
	super::onEnter();

	if (this->time.x > 0.0f && this->movement.x != 0.0f)
	{
		FiniteTimeAction* bounceX1 = EaseSineInOut::create(MoveTo::create(this->time.x, Vec2(this->movement.x, 0.0f)));
		FiniteTimeAction* bounceX2 = EaseSineInOut::create(MoveTo::create(this->time.x, Vec2(-this->movement.x, 0.0f)));

		this->sprite->runAction(RepeatForever::create(Sequence::create(bounceX1, bounceX2, nullptr)));
	}

	if (this->time.y > 0.0f && this->movement.y != 0.0f)
	{
		FiniteTimeAction* bounceY1 = EaseSineInOut::create(MoveTo::create(this->time.y, Vec2(0.0f, this->movement.y)));
		FiniteTimeAction* bounceY2 = EaseSineInOut::create(MoveTo::create(this->time.y, Vec2(0.0f, -this->movement.y)));

		this->sprite->runAction(RepeatForever::create(Sequence::create(bounceY1, bounceY2, nullptr)));
	}
}

void FloatingSprite::setFlippedX(bool isFlipped)
{
	this->sprite->setFlippedX(isFlipped);
}

void FloatingSprite::setFlippedY(bool isFlipped)
{
	this->sprite->setFlippedY(isFlipped);
}
