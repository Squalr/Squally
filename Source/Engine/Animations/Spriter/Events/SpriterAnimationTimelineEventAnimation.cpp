#include "SpriterAnimationTimelineEventAnimation.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/Spriter/Events/SpriterAnimationTimeline.h"
#include "Engine/Animations/Spriter/SpriterAnimationBone.h"
#include "Engine/Animations/Spriter/SpriterAnimationNode.h"
#include "Engine/Animations/Spriter/SpriterAnimationPart.h"
#include "Engine/Animations/Spriter/SpriterAnimationSprite.h"
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

	// Read in spriter data, mapping rotation/anchors to cocos space
	switch(animationKey.objectType)
	{
		case SpriterObjectType::Bone:
		{
			this->position = animationKey.bone.position;
			this->anchor = Vec2::ZERO;
			this->scale = animationKey.bone.scale;
			this->rotation = animationKey.bone.angle * -1.0f;
			this->alpha = animationKey.bone.alpha;
			break;
		}
		default:
		case SpriterObjectType::Object:
		{
			this->position = animationKey.object.position;
			this->anchor = animationKey.object.anchor;
			this->scale = animationKey.object.scale;
			this->rotation = animationKey.object.angle * -1.0f;
			this->alpha = animationKey.object.alpha;
			break;
		}
	}
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
	SpriterAnimationBone* bone = animation->getBoneById(this->partName);
	SpriterAnimationSprite* sprite = animation->getSpriteById(this->partName);

	if (object == nullptr || this->endTime < 0.0f)
	{
		return;
	}

	float currentTime = animation->getTimelineTime();
	
	if (currentTime >= this->keytime && currentTime < this->endTime)
	{
		if (this->next == nullptr || this->next == this || this->endTime <= this->keytime)
		{
			object->setPosition(this->position);
			//object->setScale(this->scale);
			object->setAnchorPoint(this->anchor);
			object->setRotation(this->rotation);
			object->setOpacity(GLubyte(255.0f * this->alpha));
		}
		else
		{
			// TODO: Use curve functions to transform the time ratio, this is linear right now
			float timeRatio = (currentTime - this->keytime) / (this->endTime - this->keytime);

			object->setPosition(this->position + (this->next->position - this->position) * timeRatio);
			//object->setScale(this->scale + (this->next->scale - this->scale) * timeRatio);
			object->setAnchorPoint(this->anchor + (this->next->anchor - this->anchor) * timeRatio);
			object->setRotation(this->rotation + (this->next->rotation - this->rotation) * timeRatio);
			object->setOpacity(GLubyte(255.0f * (this->alpha + (this->next->alpha - this->alpha) * timeRatio)));
		}
	}
}

void SpriterAnimationTimelineEventAnimation::onFire(SpriterAnimationNode* animation)
{
	// Not useful for animation nodes, the "event" is actually fired gradually as the event advances
}
