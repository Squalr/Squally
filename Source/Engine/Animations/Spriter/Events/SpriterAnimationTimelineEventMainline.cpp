#include "SpriterAnimationTimelineEventMainline.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/Spriter/Events/SpriterAnimationTimeline.h"
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
	this->boneParentTable = std::map<int, int>();
	this->objectParentTable = std::map<int, int>();
	this->boneNameMap = std::map<int, std::string>();
	this->objectNameMap = std::map<int, std::string>();
	this->boneIdMap = std::map<std::string, int>();
	this->objectIdMap = std::map<std::string, int>();

	for (auto boneRef : mainlineKey.boneRefs)
	{
		this->boneParentTable[boneRef.id] = boneRef.parent;

		// If the profiler doesn't like this, we can switch to parsing an {int => timeline} map when we build the timelines to avoid a linear search here
		for (const auto& animTimeline : animation.timelines)
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

void SpriterAnimationTimelineEventMainline::onEnter()
{
	super::onEnter();
}

void SpriterAnimationTimelineEventMainline::onFire(SpriterAnimationNode* animation)
{
	const std::map<std::string, SpriterAnimationBone*>& boneMap = animation->getCurrentBoneMap();
	const std::map<std::string, SpriterAnimationSprite*>& spriteMap = animation->getCurrentSpriteMap();

	// Parent all sprites
	for (const auto& part : spriteMap)
	{
		SpriterAnimationSprite* childSprite = part.second;

		if (this->objectIdMap.find(part.first) != this->objectIdMap.end() && this->objectZMap.find(part.first) != this->objectZMap.end())
		{
			int objectId = this->objectIdMap[part.first];
			int zOrder = this->objectZMap[part.first];

			childSprite->setLocalZOrder(zOrder);

			if (this->objectParentTable.find(objectId) != this->objectParentTable.end())
			{
				int parentBoneId = this->objectParentTable[objectId];

				if (this->boneNameMap.find(parentBoneId) != this->boneNameMap.end())
				{
					const std::string& parentBoneName = this->boneNameMap[parentBoneId];

					if (boneMap.find(parentBoneName) != boneMap.end())
					{
						SpriterAnimationBone* parentPart = boneMap.at(parentBoneName);

						GameUtils::changeParent(childSprite, parentPart, true);
						childSprite->setVisible(true);
						continue;
					}
				}

				// No parent -- set to root
				GameUtils::changeParent(childSprite, animation, true);
				childSprite->setVisible(true);
				continue;
			}
		}

		// hide / unparent sprite
		GameUtils::changeParent(childSprite, animation, true);
		childSprite->setVisible(false);
	}
	
	// Parent all bones
	for (const auto& part : boneMap)
	{
		SpriterAnimationBone* childBone = part.second;

		// Lazy solution to competing Z order on sibling sprites, bones should render last (BFS)
		childBone->setLocalZOrder(2048);

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

						GameUtils::changeParent(childBone, parentBone, true);
						childBone->setDebugDrawHeirarchyDepth(this->getBoneDepth(boneId));
						childBone->setVisible(true);
						continue;
					}
				}

				// No parent -- set to root
				GameUtils::changeParent(childBone, animation, true);
				childBone->setDebugDrawHeirarchyDepth(this->getBoneDepth(boneId));
				childBone->setVisible(true);
				continue;
			}
		}

		// hide / unparent bone
		GameUtils::changeParent(childBone, animation, true);
		childBone->setVisible(false);
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
