#include "SpriterAnimationTimelineEventAnimation.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/Spriter/Events/SpriterAnimationTimeline.h"
#include "Engine/Animations/Spriter/SpriterAnimationBone.h"
#include "Engine/Animations/Spriter/SpriterAnimationNode.h"
#include "Engine/Animations/Spriter/SpriterAnimationPart.h"
#include "Engine/Animations/Spriter/SpriterAnimationSprite.h"
#include "Engine/DeveloperMode/DeveloperModeController.h"
#include "Engine/Utils/MathUtils.h"

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
	this->next = this;
	this->spin = animationKey.spin;
	this->hasNoAnimationChanges = false;
	this->cascadeChildren = std::vector<SpriterAnimationTimelineEventAnimation*>();
	
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
			break;
		}
		default:
		case SpriterObjectType::Object:
		{
			this->position = animationKey.object.position;
			this->anchor = animationKey.object.anchor;
			this->scale = animationKey.object.scale;
			this->rotation = MathUtils::wrappingNormalize(animationKey.object.angle * -1.0f, 0.0f, 360.0f);
			this->alpha = animationKey.object.alpha * 255.0f;
			break;
		}
	}
	
	this->deltaPosition = Vec2::ZERO;
	this->deltaAnchor = Vec2::ZERO;
	this->deltaScale = Vec2::ZERO;
	this->deltaRotation = 0.0f;
	this->deltaAlpha = 0.0f;
}

int SpriterAnimationTimelineEventAnimation::getPartHash()
{
	return this->partHash;
}

const std::string& SpriterAnimationTimelineEventAnimation::getPartName()
{
	return this->partName;
}

SpriterAnimationTimelineEventAnimation* SpriterAnimationTimelineEventAnimation::getNext()
{
	return this->next;
}

void SpriterAnimationTimelineEventAnimation::setNext(SpriterAnimationTimelineEventAnimation* next)
{
	this->next = (next == nullptr ? this : next);
}

void SpriterAnimationTimelineEventAnimation::SpriterAnimationTimelineEventAnimation::advance(SpriterAnimationNode* animation)
{
	super::advance(animation);

	// Early exit if this animation event does not have any changes
	if (this->hasNoAnimationChanges)
	{
		return;
	}

	SpriterAnimationPart* object = animation->getPartByHash(this->partHash);

	if (object == nullptr)
	{
		return;
	}

	float currentTime = animation->getTimelineTime();
	
	if (currentTime >= this->keytime && currentTime < this->endTime)
	{
		// TODO: Use curve functions to transform the time ratio, this is linear right now
		float timeRatio = MathUtils::clamp((currentTime - this->keytime) / (this->endTime - this->keytime), 0.0f, 1.0f);

		object->setPosition(this->position + this->deltaPosition * timeRatio);
		object->setAnchorPoint(this->anchor + this->deltaAnchor * timeRatio);
		object->setScale(this->scale + this->deltaScale * timeRatio);
		object->setRotation(this->rotation + this->deltaRotation * timeRatio);
		object->setOpacity(GLubyte(this->alpha + this->deltaAlpha * timeRatio));
	}
}

void SpriterAnimationTimelineEventAnimation::onFire(SpriterAnimationNode* animation)
{
	SpriterAnimationPart* object = animation->getPartByHash(this->partHash);
	
	if (object == nullptr)
	{
		return;
	}

	object->setPosition(this->position);
	object->setAnchorPoint(this->anchor);
	object->setScale(this->scale);
	object->setRotation(this->rotation);
	object->setOpacity(GLubyte(this->alpha));
}

void SpriterAnimationTimelineEventAnimation::cascade(SpriterAnimationTimelineEventAnimation* parent)
{
	// Apply cascaded scale. Only child objects should contain the final scale. This avoids annoying render issues in cocos.
	// Mixing rotations and scales in the node heirarchy can cause skewing, so we push all scales down the hierarchy chain to sprites.
	if (parent != nullptr)
	{
		this->position = this->position * parent->scale;
		this->scale *= parent->scale;
	}
	
	for (SpriterAnimationTimelineEventAnimation* next: this->cascadeChildren)
	{
		next->cascade(this);
	}

	// Reset scale after it has been cascaded to children
	if (!this->cascadeChildren.empty())
	{
		this->scale = Vec2::ONE;
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
	// Modified shortest-rotation algorithm from https://stackoverflow.com/questions/28036652/finding-the-shortest-distance-between-two-angles/28037434
	// Key difference is that I add 540 (360 + 180) then wrap to avoid having to worry about large negative values
	this->deltaRotation = MathUtils::wrappingNormalize((this->next->rotation - this->rotation + 540.0f), 0.0f, 360.0f) - 180.0f;
	this->deltaAlpha = this->next->alpha - this->alpha;

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
