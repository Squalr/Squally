#include "SpriterAnimationTimelineEventAnimation.h"

#include "2d/CCActionInterval.h"
#include "2d/CCSprite.h"

#include "Engine/Animations/Spriter/Events/SpriterAnimationTimeline.h"
#include "Engine/Animations/Spriter/SpriterAnimationBone.h"
#include "Engine/Animations/Spriter/SpriterAnimationNode.h"
#include "Engine/Animations/Spriter/SpriterAnimationPart.h"
#include "Engine/Animations/Spriter/SpriterAnimationSprite.h"
#include "Engine/DeveloperMode/DeveloperModeController.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

#include <cmath>
#include <limits>
#include <math.h>

using namespace cocos2d;

SpriterAnimationTimelineEventAnimation* SpriterAnimationTimelineEventAnimation::create(
	SpriterAnimationTimeline* timeline,
	float keyTime,
	float endTime,
	const SpriterTimeline& keyParent,
	const SpriterTimelineKey& animationKey)
{
	SpriterAnimationTimelineEventAnimation* instance = new SpriterAnimationTimelineEventAnimation(timeline, keyTime, endTime, keyParent, animationKey);

	instance->autorelease();

	return instance;
}

SpriterAnimationTimelineEventAnimation::SpriterAnimationTimelineEventAnimation(
	SpriterAnimationTimeline* timeline,
	float keyTime,
	float endTime,
	const SpriterTimeline& keyParent,
	const SpriterTimelineKey& animationKey)
	: super(timeline, keyTime, endTime, animationKey.curveType, animationKey.c1, animationKey.c2, animationKey.c3, animationKey.c4)
{
	this->partName = keyParent.name;
	this->timelineKeyId = animationKey.id;
	this->timelineKeyTime = float(animationKey.time) / 1000.0f;
	this->sampleStartTime = this->timelineKeyTime;
	this->sampleEndTime = this->timelineKeyTime;
	this->spin = animationKey.spin;
	
	std::hash<std::string> hasher = std::hash<std::string>();
	size_t hash = hasher(this->partName);

	this->partHash = int(hash);

	// Read in spriter data, mapping rotation/anchors to cocos space
	switch(animationKey.objectType)
	{
		case SpriterObjectType::Bone:
		{
			this->position = animationKey.bone.position;
			this->anchor = Vec2::ZERO;
			this->scale = animationKey.bone.scale;
			this->rotation = MathUtils::wrappingNormalize(animationKey.bone.angle * -1.0f, 0.0f, 360.0f);
			this->alpha = animationKey.bone.alpha * 255.0f;
			this->isBone = true;
			break;
		}
		default:
		case SpriterObjectType::Object:
		{
			this->folderId = animationKey.object.folderId;
			this->fileId = animationKey.object.fileId;
			this->position = animationKey.object.position;
			this->anchor = animationKey.object.anchor;
			this->scale = animationKey.object.scale;
			this->rotation = MathUtils::wrappingNormalize(animationKey.object.angle * -1.0f, 0.0f, 360.0f);
			this->alpha = animationKey.object.alpha * 255.0f;
			this->isBone = false;
			break;
		}
	}
}

int SpriterAnimationTimelineEventAnimation::getPartHash()
{
	return this->partHash;
}

const std::string& SpriterAnimationTimelineEventAnimation::getPartName()
{
	return this->partName;
}

int SpriterAnimationTimelineEventAnimation::getTimelineKeyId() const
{
	return this->timelineKeyId;
}

float SpriterAnimationTimelineEventAnimation::getTimelineKeyTime() const
{
	return this->timelineKeyTime;
}

SpriterAnimationTimelineEventAnimation* SpriterAnimationTimelineEventAnimation::getNext()
{
	return this->next;
}

void SpriterAnimationTimelineEventAnimation::setNext(SpriterAnimationTimelineEventAnimation* next)
{
	this->next = (next == nullptr ? this : next);
}

void SpriterAnimationTimelineEventAnimation::setSamplingWindow(float sampleStartTime, float sampleEndTime, float animationLength, bool sampleTimeWraps)
{
	this->sampleStartTime = sampleStartTime;
	this->sampleEndTime = sampleEndTime;
	this->animationLength = animationLength;
	this->sampleTimeWraps = sampleTimeWraps;
}

bool SpriterAnimationTimelineEventAnimation::canAdvance()
{
	return true;
}

void SpriterAnimationTimelineEventAnimation::applyCurrentState(SpriterAnimationNode* animation)
{
	SpriterAnimationPart* object = animation->getPartByHash(this->partHash);

	if (object == nullptr)
	{
		return;
	}

	float currentTime = animation->getTimelineTime();
	
	if (currentTime >= this->keytime && currentTime < this->endTime)
	{
		if (!this->isBone)
		{
			SpriterAnimationSprite* sprite = dynamic_cast<SpriterAnimationSprite*>(object);

			if (sprite != nullptr)
			{
				sprite->setSpriteResource(animation->getSpriteResource(this->folderId, this->fileId));
			}
		}

		float sampleTime = currentTime;

		if (this->sampleTimeWraps && sampleTime < this->sampleStartTime)
		{
			sampleTime += this->animationLength;
		}

		const float duration = std::max(this->sampleEndTime - this->sampleStartTime, std::numeric_limits<float>::epsilon());
		float timeRatio = MathUtils::clamp((sampleTime - this->sampleStartTime) / duration, 0.0f, 1.0f);
		timeRatio = this->timeline->sampleCurve(timeRatio, this->curveType, this->c1, this->c2, this->c3, this->c4);

		object->applyAnimationState(
			this->position + this->deltaPosition * timeRatio,
			this->anchor + this->deltaAnchor * timeRatio,
			this->scale + this->deltaScale * timeRatio,
			this->rotation + this->deltaRotation * timeRatio,
			GLubyte(this->alpha + this->deltaAlpha * timeRatio)
		);
	}
}

void SpriterAnimationTimelineEventAnimation::advance(SpriterAnimationNode* animation)
{
	super::advance(animation);

	if (this->hasNoAnimationChanges)
	{
		return;
	}

	this->applyCurrentState(animation);
}

void SpriterAnimationTimelineEventAnimation::onFire(SpriterAnimationNode* animation)
{
	SpriterAnimationPart* object = animation->getPartByHash(this->partHash);
	
	if (object == nullptr)
	{
		return;
	}

	if (!this->isBone)
	{
		SpriterAnimationSprite* sprite = dynamic_cast<SpriterAnimationSprite*>(object);

		if (sprite != nullptr)
		{
			sprite->setSpriteResource(animation->getSpriteResource(this->folderId, this->fileId));
		}
	}

	object->applyAnimationState(this->position, this->anchor, this->scale, this->rotation, GLubyte(this->alpha));
}

void SpriterAnimationTimelineEventAnimation::cascade(SpriterAnimationTimelineEventAnimation* parent)
{
	for (SpriterAnimationTimelineEventAnimation* next: this->cascadeChildren)
	{
		next->cascade(this);
	}
}

void SpriterAnimationTimelineEventAnimation::addCascadeChild(SpriterAnimationTimelineEventAnimation* cascadeChild)
{
	this->cascadeChildren.push_back(cascadeChild);
}

void SpriterAnimationTimelineEventAnimation::clearCascadeChildren()
{
	this->cascadeChildren.clear();
}

void SpriterAnimationTimelineEventAnimation::computeDeltas()
{
	this->deltaPosition = this->next->position - this->position;
	this->deltaAnchor = this->next->anchor - this->anchor;
	this->deltaScale = this->next->scale - this->scale;
	this->deltaAlpha = this->next->alpha - this->alpha;
	float nextRotation = this->next->rotation;

	// Mirror Spriter++ AngleInfo::angleLinear() so legacy/new interpolation agree exactly.
	if (this->spin == 0)
	{
		nextRotation = this->rotation;
	}
	else if (this->spin > 0)
	{
		if (this->rotation < nextRotation)
		{
			nextRotation -= 360.0f;
		}
	}
	else
	{
		if (nextRotation < this->rotation)
		{
			nextRotation += 360.0f;
		}
	}

	this->deltaRotation = nextRotation - this->rotation;

	this->hasNoAnimationChanges = this->deltaPosition == Vec2::ZERO
		&& this->deltaAnchor == Vec2::ZERO
		&& this->deltaScale == Vec2::ZERO
		&& this->deltaRotation == 0.0f
		&& this->deltaAlpha == 0.0f;

	for (SpriterAnimationTimelineEventAnimation* next: this->cascadeChildren)
	{
		next->computeDeltas();
	}
}
