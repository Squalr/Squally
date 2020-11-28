#include "SpriterAnimationTimelineEventBase.h"

#include "cocos/2d/CCSprite.h"

using namespace cocos2d;

SpriterAnimationTimelineEventBase::SpriterAnimationTimelineEventBase(float startTime, float endTime)
{
	this->startTime = startTime;
	this->endTime = endTime;
	this->hasFired = false;
}

void SpriterAnimationTimelineEventBase::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void SpriterAnimationTimelineEventBase::reset()
{
	this->hasFired = false;
}

void SpriterAnimationTimelineEventBase::advance(float elapsedTime)
{
	if (!this->hasFired && elapsedTime > this->startTime)
	{
		this->hasFired = true;
		this->onFire();
	}
}

