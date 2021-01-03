#include "SpriterAnimationSprite.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/Spriter/SpriterAnimationBone.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

SpriterAnimationSprite* SpriterAnimationSprite::create(std::string spriteResource, Vec2 anchor)
{
	SpriterAnimationSprite* instance = new SpriterAnimationSprite(spriteResource, anchor);

	instance->autorelease();

	return instance;
}

SpriterAnimationSprite::SpriterAnimationSprite(std::string spriteResource, Vec2 anchor)
{
	this->sprite = Sprite::create(spriteResource);

	// Not super useful since we just overwrite this during animation events
	this->sprite->setAnchorPoint(anchor);

	this->addChild(this->sprite);
}

SpriterAnimationSprite::~SpriterAnimationSprite()
{
}

void SpriterAnimationSprite::setAnchorPoint(const Vec2& anchorPoint)
{
	this->sprite->setAnchorPoint(anchorPoint);
}

void SpriterAnimationSprite::setScaleX(float scaleX)
{
	this->sprite->setScaleX(scaleX);
}

void SpriterAnimationSprite::setScaleY(float scaleY)
{
	this->sprite->setScaleX(scaleY);
}
