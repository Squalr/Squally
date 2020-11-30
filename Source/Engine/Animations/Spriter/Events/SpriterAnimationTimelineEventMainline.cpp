#include "SpriterAnimationTimelineEventMainline.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/Spriter/Events/SpriterAnimationTimeline.h"

using namespace cocos2d;

SpriterAnimationTimelineEventMainline* SpriterAnimationTimelineEventMainline::create(SpriterAnimationTimeline* timeline, float endTime, const SpriterMainlineKey& mainlineKey)
{
	SpriterAnimationTimelineEventMainline* instance = new SpriterAnimationTimelineEventMainline(timeline, endTime, mainlineKey);

	instance->autorelease();

	return instance;
}

SpriterAnimationTimelineEventMainline::SpriterAnimationTimelineEventMainline(SpriterAnimationTimeline* timeline, float endTime, const SpriterMainlineKey& mainlineKey)
	: super(timeline, mainlineKey.time, endTime, mainlineKey.curveType, mainlineKey.c1, mainlineKey.c2, mainlineKey.c3, mainlineKey.c4)
{
}

void SpriterAnimationTimelineEventMainline::onEnter()
{
	super::onEnter();
}

void SpriterAnimationTimelineEventMainline::onFire(SpriterAnimationNode* animation)
{
}
