#include "SpriterAnimationPart.h"

#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

SpriterAnimationPart::SpriterAnimationPart()
{
}

SpriterAnimationPart::~SpriterAnimationPart()
{
}

void SpriterAnimationPart::addAnimationPartChild(SpriterAnimationPart* part)
{
    part->parentPart = this;
    this->childAnimationParts.push_back(part);
    
    GameUtils::changeParent(part, this, false);
}

void SpriterAnimationPart::clearAnimationPartChildren()
{
    this->childAnimationParts.clear();
}

void SpriterAnimationPart::setTimelineCanUpdate(bool canUpdate)
{
	this->timelineCanUpdate = canUpdate;
}

bool SpriterAnimationPart::canTimelineUpdate() const
{
	return this->timelineCanUpdate;
}

void SpriterAnimationPart::setAnimationOffset(const Vec2& offset)
{
	this->animationOffset = offset;
}

const Vec2& SpriterAnimationPart::getAnimationOffset() const
{
	return this->animationOffset;
}

void SpriterAnimationPart::setAlphaOverride(float alphaOverride)
{
	this->alphaOverride = alphaOverride;

	// -1 means clear override and use timeline alpha.
	if (this->alphaOverride >= 0.0f)
	{
		super::setOpacity(GLubyte(this->alphaOverride * 255.0f));
	}
}

float SpriterAnimationPart::getAlphaOverride() const
{
	return this->alphaOverride;
}

void SpriterAnimationPart::setOpacity(GLubyte opacity)
{
	if (this->alphaOverride >= 0.0f)
	{
		super::setOpacity(GLubyte(this->alphaOverride * 255.0f));
		return;
	}

	super::setOpacity(opacity);
}
