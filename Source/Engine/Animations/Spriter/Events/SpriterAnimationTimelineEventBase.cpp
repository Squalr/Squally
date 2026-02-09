#include "SpriterAnimationTimelineEventBase.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/Spriter/Events/SpriterAnimationTimeline.h"
#include "Engine/Animations/Spriter/SpriterAnimationNode.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;

SpriterAnimationTimelineEventBase::SpriterAnimationTimelineEventBase(SpriterAnimationTimeline* timeline, float keytime, float endTime, SpriterCurveType curveType, float c1, float c2, float c3, float c4)
{
	this->timeline = timeline;
	this->keytime = keytime / 1000.0f;
	this->endTime = endTime / 1000.0f;
	this->curveType = curveType;
	this->c1 = c1;
	this->c2 = c2;
	this->c3 = c3;
	this->c4 = c4;
}

float SpriterAnimationTimelineEventBase::getKeyTime()
{
	return this->keytime;
}

float SpriterAnimationTimelineEventBase::getEndTime()
{
	return this->endTime;
}

void SpriterAnimationTimelineEventBase::advance(SpriterAnimationNode* animation)
{
	const float previousTime = animation->getPreviousTimelineTime();
	const float currentTime = animation->getTimelineTime();
	const bool timeWrapped = previousTime > currentTime;
	bool crossedKey = false;

	if (timeWrapped)
	{
		// Wrapped from end -> start. Fire keys crossed in both segments:
		// (previous, animationEnd] U [0, current].
		crossedKey = this->keytime > previousTime || this->keytime <= currentTime;
	}
	else
	{
		crossedKey = previousTime <= this->keytime && currentTime > this->keytime;
	}

	if (crossedKey)
	{
		this->onFire(animation);
	}
}
