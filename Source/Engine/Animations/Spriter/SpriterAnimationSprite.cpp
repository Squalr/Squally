#include "SpriterAnimationSprite.h"

#include "2d/CCSprite.h"

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
	this->originalSpriteResource = spriteResource;
	this->timelineSpriteResource = spriteResource;
	this->currentSpriteResource = spriteResource;
	this->currentAnchor = anchor;

	this->addChild(this->sprite);
	this->refreshSpriteLayout();
}

SpriterAnimationSprite::~SpriterAnimationSprite()
{
}

void SpriterAnimationSprite::setAnchorPoint(const Vec2& anchorPoint)
{
	this->currentAnchor = anchorPoint;
	this->refreshSpriteLayout();
}

void SpriterAnimationSprite::setScaleX(float scaleX)
{
	super::setScaleX(scaleX);
}

void SpriterAnimationSprite::setScaleY(float scaleY)
{
	super::setScaleY(scaleY);
}

void SpriterAnimationSprite::setSpriteResource(const std::string& spriteResource)
{
	if (this->sprite == nullptr || spriteResource.empty())
	{
		return;
	}

	this->timelineSpriteResource = spriteResource;

	if (this->overrideSpriteResource.empty())
	{
		this->applySpriteResource(spriteResource);
	}
}

void SpriterAnimationSprite::setSpriteResourceOverride(const std::string& spriteResource)
{
	if (this->sprite == nullptr || spriteResource.empty())
	{
		return;
	}

	this->overrideSpriteResource = spriteResource;
	this->applySpriteResource(spriteResource);
}

void SpriterAnimationSprite::restoreSpriteResource()
{
	this->overrideSpriteResource.clear();
	this->applySpriteResource(this->timelineSpriteResource.empty() ? this->originalSpriteResource : this->timelineSpriteResource);
}

std::string SpriterAnimationSprite::getSpriteResource() const
{
	return this->currentSpriteResource;
}

CSize SpriterAnimationSprite::getSpriteSize() const
{
	return this->sprite == nullptr ? CSize::ZERO : this->sprite->getContentSize();
}

void SpriterAnimationSprite::applySpriteResource(const std::string& spriteResource)
{
	if (this->sprite == nullptr || spriteResource.empty() || this->currentSpriteResource == spriteResource)
	{
		return;
	}

	this->currentSpriteResource = spriteResource;
	this->sprite->setTexture(spriteResource);
	this->refreshSpriteLayout();
}

void SpriterAnimationSprite::applyAnchorPoint(const Vec2& anchorPoint)
{
	this->currentAnchor = anchorPoint;
	this->refreshSpriteLayout();
}

void SpriterAnimationSprite::applyAnimationOffset(const Vec2& offset)
{
	this->refreshSpriteLayout();
}

void SpriterAnimationSprite::refreshSpriteLayout()
{
	if (this->sprite == nullptr)
	{
		return;
	}

	this->setContentSize(CSize::ZERO);
	this->sprite->setAnchorPoint(this->currentAnchor);
	super::setAnchorPoint(Vec2::ZERO);
	this->sprite->setPosition(this->animationOffset);
}
