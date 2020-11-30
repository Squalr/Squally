#include "SpriterAnimationTimelineEventMainline.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/Spriter/Events/SpriterAnimationTimeline.h"
#include "Engine/Utils/GameUtils.h"

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
	this->boneParentTable = std::map<int, int>();
	this->objectParentTable = std::map<int, int>();

	for (auto boneRef : mainlineKey.boneRefs)
	{
		this->boneParentTable[boneRef.id] = boneRef.parent;
	}

	for (auto objectRef : mainlineKey.objectRefs)
	{
		this->objectParentTable[objectRef.id] = objectRef.parent;
	}
}

void SpriterAnimationTimelineEventMainline::onEnter()
{
	super::onEnter();
}

void SpriterAnimationTimelineEventMainline::onFire(SpriterAnimationNode* animation)
{
	
}
