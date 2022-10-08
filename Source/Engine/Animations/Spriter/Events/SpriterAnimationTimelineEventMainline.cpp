#include "SpriterAnimationTimelineEventMainline.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/Spriter/Events/SpriterAnimationTimeline.h"
#include "Engine/Animations/Spriter/Events/SpriterAnimationTimelineEventAnimation.h"
#include "Engine/Animations/Spriter/SpriterAnimationBone.h"
#include "Engine/Animations/Spriter/SpriterAnimationNode.h"
#include "Engine/Animations/Spriter/SpriterAnimationPart.h"
#include "Engine/Animations/Spriter/SpriterAnimationSprite.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

SpriterAnimationTimelineEventMainline* SpriterAnimationTimelineEventMainline::create(SpriterAnimationTimeline* timeline, float endTime, const SpriterAnimation& animation, const SpriterMainlineKey& mainlineKey)
{
	SpriterAnimationTimelineEventMainline* instance = new SpriterAnimationTimelineEventMainline(timeline, endTime, animation, mainlineKey);

	instance->autorelease();

	return instance;
}

SpriterAnimationTimelineEventMainline::SpriterAnimationTimelineEventMainline(SpriterAnimationTimeline* timeline, float endTime, const SpriterAnimation& animation, const SpriterMainlineKey& mainlineKey)
	: super(timeline, float(mainlineKey.time), endTime, mainlineKey.curveType, mainlineKey.c1, mainlineKey.c2, mainlineKey.c3, mainlineKey.c4)
{
	for (const SpriterBoneRef& boneRef : mainlineKey.boneRefs)
	{
		this->boneParentTable[boneRef.id] = boneRef.parent;

		// If the profiler doesn't like this, we can switch to parsing an {int => timeline} map when we build the timelines to avoid a linear search here
		for (const SpriterTimeline& animTimeline : animation.timelines)
		{
			if (animTimeline.id == boneRef.timeline)
			{
				this->boneIdMap[animTimeline.name] = boneRef.id;
				this->boneNameMap[boneRef.id] = animTimeline.name;
			}
		}
	}

	for (auto objectRef : mainlineKey.objectRefs)
	{
		this->objectParentTable[objectRef.id] = objectRef.parent;

		// If the profiler doesn't like this, we can switch to parsing an {int => timeline} map when we build the timelines to avoid a linear search here
		for (const auto& animTimeline : animation.timelines)
		{
			if (animTimeline.id == objectRef.timeline)
			{
				this->objectIdMap[animTimeline.name] = objectRef.id;
				this->objectZMap[animTimeline.name] = objectRef.zIndex;
				this->objectNameMap[objectRef.id] = animTimeline.name;
			}
		}
	}
}

void SpriterAnimationTimelineEventMainline::registerAnimation(SpriterAnimationTimelineEventAnimation* animationEvent)
{
	this->registeredAnimationEventsByPartName[animationEvent->getPartName()] = animationEvent;
}

void SpriterAnimationTimelineEventMainline::onFire(SpriterAnimationNode* animation)
{
	const std::map<std::string, SpriterAnimationBone*>& boneMap = animation->getCurrentBoneMap();
	const std::map<std::string, SpriterAnimationSprite*>& spriteMap = animation->getCurrentSpriteMap();

	// Known issue -- bone structures like this fail:
	//           b
	//      b         b
	//    z1, z3      z2
	// The first bone has sprites of z order 1 and 3, and the second has a z order of 2. These conflict in a parent heirarchy chain.
	// The only solution that would allow for parent heirarchies is to clone the first bone, splitting it into two.

	for (const auto& part : boneMap)
	{
		SpriterAnimationBone* childBone = part.second;
		childBone->clearAnimationPartChildren();
	}

	for (const auto& part : spriteMap)
	{
		SpriterAnimationSprite* childSprite = part.second;
		childSprite->clearAnimationPartChildren();
	}

	animation->clearAnimationPartChildren();
	
	// Parent all bones
	for (const auto& part : boneMap)
	{
		SpriterAnimationBone* childBone = part.second;
		childBone->setLocalZOrder(0);
		
		if (this->boneIdMap.find(part.first) != this->boneIdMap.end())
		{
			int boneId = this->boneIdMap[part.first];

			if (this->boneParentTable.find(boneId) != this->boneParentTable.end())
			{
				int parentBoneId = this->boneParentTable[boneId];

				if (this->boneNameMap.find(parentBoneId) != this->boneNameMap.end())
				{
					const std::string& parentBoneName = this->boneNameMap[parentBoneId];

					if (boneMap.find(parentBoneName) != boneMap.end())
					{
						SpriterAnimationBone* parentBone = boneMap.at(parentBoneName);

						parentBone->addAnimationPartChild(childBone);
						childBone->setDebugDrawHeirarchyDepth(this->getBoneDepth(boneId));
						childBone->setVisible(true);
						continue;
					}
				}

				// No parent -- set to root
				animation->addAnimationPartChild(childBone);
				childBone->setDebugDrawHeirarchyDepth(this->getBoneDepth(boneId));
				childBone->setVisible(true);
				continue;
			}
		}

		// hide / unparent bone
		animation->addAnimationPartChild(childBone);
		childBone->setVisible(false);
	}

	// Parent all sprites
	for (const auto& part : spriteMap)
	{
		SpriterAnimationSprite* childSprite = part.second;

		if (this->objectZMap.find(part.first) != this->objectZMap.end())
		{
			int objectId = this->objectIdMap[part.first];
			int zOrder = this->objectZMap[part.first];

			if (this->objectParentTable.find(objectId) != this->objectParentTable.end())
			{
				animation->addAnimationPartChild(childSprite);
				childSprite->setLocalZOrder(zOrder);
				childSprite->setVisible(true);
				continue;
			}
		}

		// hide / unparent sprite
		animation->addAnimationPartChild(childSprite);
		childSprite->setVisible(false);
	}
}

void SpriterAnimationTimelineEventMainline::buildAnimationHeirarchy()
{
	for (const auto& next : this->registeredAnimationEventsByPartName)
	{
		auto key = next.first;
		auto animationEvent = next.second;
		animationEvent->clearCascadeChildren();
	}
	
	// Parent all timeline events
	for (const auto& next : this->registeredAnimationEventsByPartName)
	{
		auto childObjectName = next.first;
		auto animationEvent = next.second;

		if (this->boneIdMap.find(childObjectName) != this->boneIdMap.end() && this->registeredAnimationEventsByPartName.find(childObjectName) != this->registeredAnimationEventsByPartName.end())
		{
			int boneId = this->boneIdMap[childObjectName];

			if (this->boneParentTable.find(boneId) != this->boneParentTable.end())
			{
				int parentBoneId = this->boneParentTable[boneId];

				if (this->boneNameMap.find(parentBoneId) != this->boneNameMap.end())
				{
					const std::string& parentBoneName = this->boneNameMap[parentBoneId];

					if (registeredAnimationEventsByPartName.find(parentBoneName) != registeredAnimationEventsByPartName.end())
					{
						SpriterAnimationTimelineEventAnimation* parentEvent = this->registeredAnimationEventsByPartName[parentBoneName];

						parentEvent->addCascadeChild(animationEvent);
						continue;
					}
				}
			}
		}
		else if (this->objectIdMap.find(childObjectName) != this->objectIdMap.end() && this->registeredAnimationEventsByPartName.find(childObjectName) != this->registeredAnimationEventsByPartName.end())
		{
			int objectId = this->objectIdMap[childObjectName];

			if (this->objectParentTable.find(objectId) != this->objectParentTable.end())
			{
				int parentBoneId = this->objectParentTable[objectId];

				if (this->boneNameMap.find(parentBoneId) != this->boneNameMap.end())
				{
					const std::string& parentBoneName = this->boneNameMap[parentBoneId];

					if (registeredAnimationEventsByPartName.find(parentBoneName) != registeredAnimationEventsByPartName.end())
					{
						SpriterAnimationTimelineEventAnimation* parentEvent = this->registeredAnimationEventsByPartName[parentBoneName];

						parentEvent->addCascadeChild(animationEvent);
						continue;
					}
				}
			}
		}

		this->roots.push_back(animationEvent);
	}

	for (SpriterAnimationTimelineEventAnimation* next : this->roots)
	{
		next->cascade();
	}
}

void SpriterAnimationTimelineEventMainline::buildDeltas()
{
	for (SpriterAnimationTimelineEventAnimation* next : this->roots)
	{
		next->computeDeltas();
	}
}

int SpriterAnimationTimelineEventMainline::getBoneDepth(int boneId)
{
	int depth = 0;
	
	while (this->boneParentTable.find(boneId) != this->boneParentTable.end())
	{
		boneId = boneParentTable[boneId];
		depth++;
		
		// Fail safe, should never happen
		if (depth >= 256)
		{
			break;
		}
	}

	return depth;
}
