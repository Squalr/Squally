#include "SpriterAnimationTimelineEventAnimation.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/Spriter/Events/SpriterAnimationTimeline.h"
#include "Engine/Animations/Spriter/SpriterAnimationBone.h"
#include "Engine/Animations/Spriter/SpriterAnimationNode.h"
#include "Engine/Animations/Spriter/SpriterAnimationPart.h"
#include "Engine/DeveloperMode/DeveloperModeController.h"

using namespace cocos2d;

SpriterAnimationTimelineEventAnimation* SpriterAnimationTimelineEventAnimation::create(
	SpriterAnimationTimeline* timeline,
	float endTime,
	const SpriterTimeline& keyParent,
	const SpriterTimelineKey& animationKey)
{
	SpriterAnimationTimelineEventAnimation* instance = new SpriterAnimationTimelineEventAnimation(timeline, endTime, keyParent, animationKey);

	instance->autorelease();

	return instance;
}

SpriterAnimationTimelineEventAnimation::SpriterAnimationTimelineEventAnimation(
	SpriterAnimationTimeline* timeline,
	float endTime,
	const SpriterTimeline& keyParent,
	const SpriterTimelineKey& animationKey)
	: super(timeline, float(animationKey.time), endTime, animationKey.curveType, animationKey.c1, animationKey.c2, animationKey.c3, animationKey.c4)
{
	this->partName = keyParent.name;
	this->next = nullptr;

	switch(animationKey.objectType)
	{
		case SpriterObjectType::Bone:
		{
			this->position = animationKey.bone.position;
			// We don't actually want to set the scale for bones -- scale for bones does not propagate. It is only used in draw size for the debug boxes.
			this->debugDrawScale = animationKey.bone.scale;
			this->scale = Vec2::ONE;
			this->rotation = animationKey.bone.angle;
			this->alpha = animationKey.bone.alpha;
			break;
		}
		default:
		case SpriterObjectType::Object:
		{
			this->position = animationKey.object.position;
			this->scale = animationKey.object.scale;
			this->debugDrawScale = Vec2::ONE;
			this->rotation = animationKey.object.angle;
			this->alpha = animationKey.object.alpha;
			break;
		}
	}

	// Map spriter rotation to cocos rotation
	this->rotation *= -1.0f;
}

SpriterAnimationTimelineEventAnimation* SpriterAnimationTimelineEventAnimation::getNext()
{
	return this->next;
}

void SpriterAnimationTimelineEventAnimation::setNext(SpriterAnimationTimelineEventAnimation* next)
{
	this->next = next;
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
	
	if (currentTime >= this->keytime && currentTime < this->endTime)
	{
		if (this->next == nullptr || this->endTime <= this->keytime)
		{
			object->setPosition(this->position);
			object->setScaleX(this->scale.x);
			object->setScaleY(this->scale.y);
			object->setRotation(this->rotation);
			object->setOpacity(GLubyte(255.0f * this->alpha));

			// Debug draw info
			if (DeveloperModeController::isDeveloperModeEnabled())
			{
				SpriterAnimationBone* bone = animation->getBoneById(this->partName);

				if (bone != nullptr)
				{
					bone->setDebugDrawBoneScale(this->debugDrawScale);
				}
			}
		}
		else
		{
			// TODO: Use curve functions to transform the time ratio, this is linear right now
			float timeRatio = (currentTime - this->keytime) / (this->endTime - this->keytime);

			object->setPosition(this->position + (this->next->position - this->position) * timeRatio);
			object->setScaleX(this->scale.x + (this->next->scale.x - this->scale.x) * timeRatio);
			object->setScaleY(this->scale.y + (this->next->scale.y - this->scale.y) * timeRatio);
			object->setRotation(this->rotation + (this->next->rotation - this->rotation) * timeRatio);
			object->setOpacity(GLubyte(255.0f * (this->alpha + (this->next->alpha - this->alpha) * timeRatio)));

			// Debug draw info
			if (DeveloperModeController::isDeveloperModeEnabled())
			{
				SpriterAnimationBone* bone = animation->getBoneById(this->partName);

				if (bone != nullptr)
				{
					bone->setDebugDrawBoneScale(this->debugDrawScale + (this->next->debugDrawScale - this->debugDrawScale) * timeRatio);
				}
			}
		}
	}
}

void SpriterAnimationTimelineEventAnimation::onFire(SpriterAnimationNode* animation)
{
	// Not useful for animation nodes, the "event" is actually fired gradually as the event advances
}
