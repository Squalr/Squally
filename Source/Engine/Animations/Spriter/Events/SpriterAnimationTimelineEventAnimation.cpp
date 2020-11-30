#include "SpriterAnimationTimelineEventAnimation.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/Spriter/Events/SpriterAnimationTimeline.h"
#include "Engine/Animations/Spriter/SpriterAnimationNode.h"
#include "Engine/Animations/Spriter/SpriterAnimationPart.h"

using namespace cocos2d;

SpriterAnimationTimelineEventAnimation* SpriterAnimationTimelineEventAnimation::create(SpriterAnimationTimeline* timeline, float endTime, const SpriterTimeline& keyParent, const SpriterTimelineKey& animationKey)
{
	SpriterAnimationTimelineEventAnimation* instance = new SpriterAnimationTimelineEventAnimation(timeline, endTime, keyParent, animationKey);

	instance->autorelease();

	return instance;
}

SpriterAnimationTimelineEventAnimation::SpriterAnimationTimelineEventAnimation(SpriterAnimationTimeline* timeline, float endTime, const SpriterTimeline& keyParent, const SpriterTimelineKey& animationKey)
	: super(timeline, animationKey.time, endTime, animationKey.curveType, animationKey.c1, animationKey.c2, animationKey.c3, animationKey.c4)
{
	this->partName = keyParent.name;

	switch(animationKey.objectType)
	{
		case SpriterObjectType::Bone:
		{
			this->position = animationKey.bone.position;
			this->scale = animationKey.bone.scale;
			this->rotation = animationKey.bone.angle;
			break;
		}
		default:
		case SpriterObjectType::Object:
		{
			this->position = animationKey.object.position;
			this->scale = animationKey.object.scale;
			this->rotation = animationKey.object.angle;
			break;
		}
	}
}

void SpriterAnimationTimelineEventAnimation::SpriterAnimationTimelineEventAnimation::advance(SpriterAnimationNode* animation)
{
	super::advance(animation);
	
	SpriterAnimationPart* object = animation->getPartById(this->partName);

	if (object == nullptr)
	{
		return;
	}

	float currentTime = animation->getTimelineTime();
}

void SpriterAnimationTimelineEventAnimation::onFire(SpriterAnimationNode* animation)
{
	// Not useful for animation nodes, the "event" is actually fired gradually as the event advances
}
