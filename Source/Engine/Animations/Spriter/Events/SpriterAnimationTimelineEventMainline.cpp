#include "SpriterAnimationTimelineEventMainline.h"

#include "cocos/2d/CCSprite.h"

using namespace cocos2d;

SpriterAnimationTimelineEventMainline* SpriterAnimationTimelineEventMainline::create(const SpriterMainlineKey& mainlineData, float endTime)
{
	SpriterAnimationTimelineEventMainline* instance = new SpriterAnimationTimelineEventMainline(mainlineData, endTime);

	instance->autorelease();

	return instance;
}

SpriterAnimationTimelineEventMainline::SpriterAnimationTimelineEventMainline(const SpriterMainlineKey& mainlineData, float endTime) : super(mainlineData.time, endTime)
{
	this->mainlineData = mainlineData;
}

void SpriterAnimationTimelineEventMainline::onEnter()
{
	super::onEnter();
}

SpriterCurveType SpriterAnimationTimelineEventMainline::getCurveType()
{
	return this->mainlineData.curveType;
}

void SpriterAnimationTimelineEventMainline::onFire()
{
}
