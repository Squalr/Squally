#include "SpriterAnimationTimelineEventAnimation.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/Spriter/Events/SpriterAnimationTimeline.h"
#include "Engine/Animations/Spriter/SpriterAnimationNode.h"
#include "Engine/Animations/Spriter/SpriterAnimationPart.h"

using namespace cocos2d;

SpriterAnimationTimelineEventAnimation* SpriterAnimationTimelineEventAnimation::create(
	SpriterAnimationTimeline* timeline,
	float endTime,
	const SpriterTimeline& keyParent,
	const SpriterTimelineKey& animationKey,
	SpriterAnimationTimelineEventAnimation* previous)
{
	SpriterAnimationTimelineEventAnimation* instance = new SpriterAnimationTimelineEventAnimation(timeline, endTime, keyParent, animationKey, previous);

	instance->autorelease();

	return instance;
}

SpriterAnimationTimelineEventAnimation::SpriterAnimationTimelineEventAnimation(
	SpriterAnimationTimeline* timeline,
	float endTime,
	const SpriterTimeline& keyParent,
	const SpriterTimelineKey& animationKey,
	SpriterAnimationTimelineEventAnimation* previous)
	: super(timeline, animationKey.time, endTime, animationKey.curveType, animationKey.c1, animationKey.c2, animationKey.c3, animationKey.c4)
{
	this->partName = keyParent.name;
	this->previous = previous;

	switch(animationKey.objectType)
	{
		case SpriterObjectType::Bone:
		{
			this->position = animationKey.bone.position;
			this->scale = animationKey.bone.scale;
			this->rotation = animationKey.bone.angle;
			this->alpha = animationKey.bone.alpha;
			break;
		}
		default:
		case SpriterObjectType::Object:
		{
			this->position = animationKey.object.position;
			this->scale = animationKey.object.scale;
			this->rotation = animationKey.object.angle;
			this->alpha = animationKey.object.alpha;
			break;
		}
	}
}

void SpriterAnimationTimelineEventAnimation::SpriterAnimationTimelineEventAnimation::advance(SpriterAnimationNode* animation)
{
	super::advance(animation);

	SpriterAnimationPart* object = animation->getPartById(this->partName);

	if (object == nullptr || this->endTime < 0.0f)
	{
		return;
	}

	float currentTime = animation->getTimelineTime();
	float previousTime = animation->getPreviousTimelineTime();
	
	if (currentTime >= this->keytime && currentTime < this->endTime)
	{
		// TODO: Use curve functions to transform the time ratio, this is linear right now
		float timeRatio = (this->keytime - currentTime) / this->endTime;

		const Vec2& basePosition = previous == nullptr ? Vec2::ZERO : this->previous->position;
		const Vec2& baseScale = previous == nullptr ? Vec2::ONE : this->previous->scale;
		const float baseRotation = previous == nullptr ? 0.0f : this->previous->rotation;
		const float baseAlpha = previous == nullptr ? 1.0f : float(this->previous->alpha);

		object->setPosition(basePosition + (this->position - basePosition) * timeRatio);
		object->setScaleX(baseScale.x + (this->scale.x - baseScale.x) * timeRatio);
		object->setScaleY(baseScale.y + (this->scale.y - baseScale.y) * timeRatio);
		object->setRotation(baseRotation + (this->rotation - baseRotation) * timeRatio);
		object->setOpacity(GLubyte(255.0f * (baseAlpha + (this->alpha - baseAlpha) * timeRatio)));
	}
}

void SpriterAnimationTimelineEventAnimation::onFire(SpriterAnimationNode* animation)
{
	// Not useful for animation nodes, the "event" is actually fired gradually as the event advances
}
