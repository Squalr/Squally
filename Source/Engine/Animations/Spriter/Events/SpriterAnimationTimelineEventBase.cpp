#include "SpriterAnimationTimelineEventBase.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/Spriter/Events/SpriterAnimationTimeline.h"
#include "Engine/Animations/Spriter/SpriterAnimationNode.h"

using namespace cocos2d;

SpriterAnimationTimelineEventBase::SpriterAnimationTimelineEventBase(SpriterAnimationTimeline* timeline, float startTime, float endTime, SpriterCurveType curveType, float c1, float c2, float c3, float c4)
{
	this->timeline = timeline;
	this->startTime = startTime;
	this->endTime = endTime;
	this->curveType = curveType;
	this->c1 = c1;
	this->c2 = c2;
	this->c3 = c3;
	this->c4 = c4;
}

void SpriterAnimationTimelineEventBase::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void SpriterAnimationTimelineEventBase::advance(SpriterAnimationNode* animation)
{
	if (animation->getPreviousTimelineTime() < this->startTime && animation->getTimelineTime() > this->startTime)
	{
		this->onFire(animation);
	}
}
