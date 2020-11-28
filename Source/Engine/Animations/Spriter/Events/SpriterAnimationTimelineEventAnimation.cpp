#include "SpriterAnimationTimelineEventAnimation.h"

#include "cocos/2d/CCSprite.h"

using namespace cocos2d;

SpriterAnimationTimelineEventAnimation* SpriterAnimationTimelineEventAnimation::create(float startTime, float endTime)
{
	SpriterAnimationTimelineEventAnimation* instance = new SpriterAnimationTimelineEventAnimation(startTime, endTime);

	instance->autorelease();

	return instance;
}

SpriterAnimationTimelineEventAnimation::SpriterAnimationTimelineEventAnimation(float startTime, float endTime) : super(startTime, endTime)
{
	this->elapsedTime = 0.0f;
}

void SpriterAnimationTimelineEventAnimation::SpriterAnimationTimelineEventAnimation::advance(float elapsedTime)
{
	// TODO: LERP
}

void SpriterAnimationTimelineEventAnimation::onFire()
{
	// Not useful for animation nodes, the "event" is actually fired gradually as the event advances
}
