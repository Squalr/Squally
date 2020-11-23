#include "SpriterAnimationTimelineEventBase.h"

#include "cocos/2d/CCSprite.h"

using namespace cocos2d;

SpriterAnimationTimelineEventBase::SpriterAnimationTimelineEventBase(SpriterAnimationNode* animations, float startTime, float endTime)
{
	this->animations = animations;
	this->startTime = startTime;
	this->endTime = endTime;
	this->childTimelineEvents = std::vector<SpriterAnimationTimelineEventBase*>();
	this->hasFired = false;
}

void SpriterAnimationTimelineEventBase::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void SpriterAnimationTimelineEventBase::advance(float elapsedTime)
{
	if (!this->hasFired && elapsedTime > this->startTime)
	{
		this->hasFired = true;
		this->onFire();
	}
}

