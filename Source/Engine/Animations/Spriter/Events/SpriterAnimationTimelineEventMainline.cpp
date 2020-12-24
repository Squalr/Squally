#include "SpriterAnimationTimelineEventMainline.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/Spriter/Events/SpriterAnimationTimeline.h"
#include "Engine/Animations/Spriter/SpriterAnimationBone.h"
#include "Engine/Animations/Spriter/SpriterAnimationNode.h"
#include "Engine/Animations/Spriter/SpriterAnimationPart.h"
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
	this->boneIdMap = std::map<std::string, int>();
	this->boneNameMap = std::map<int, std::string>();
	this->objectParentTable = std::map<int, int>();

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
	}
}

void SpriterAnimationTimelineEventMainline::onEnter()
{
	super::onEnter();
}

void SpriterAnimationTimelineEventMainline::onFire(SpriterAnimationNode* animation)
{
	const std::map<std::string, SpriterAnimationBone*>& boneMap = animation->getCurrentBoneMap();
	const std::map<std::string, SpriterAnimationPart*>& spriteMap = animation->getCurrentSpriteMap();

	// Parent all bones first
	for (const auto& part : boneMap)
	{
		SpriterAnimationBone* childPart = part.second;

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
						SpriterAnimationBone* parentPart = boneMap.at(parentBoneName);

						GameUtils::changeParent(childPart, parentPart, true);
						childPart->setDebugDrawHeirarchyDepth(this->getBoneDepth(boneId));
						childPart->setVisible(true);
						continue;
					}
				}

				// No parent -- set to root
				GameUtils::changeParent(childPart, animation, true);
				childPart->setDebugDrawHeirarchyDepth(this->getBoneDepth(boneId));
				childPart->setVisible(true);
				continue;
			}
		}

		// hide / unparent bone
		GameUtils::changeParent(childPart, animation, true);
		childPart->setVisible(false);
	}

	// Parent all sprites
	for (const auto& part : spriteMap)
	{
		// Temp debugging
		part.second->setVisible(false);
	}
}

void SpriterAnimationTimelineEventMainline::reparentAnimationPart(std::string partName, SpriterAnimationPart* part, std::map<int, int>& parentTable)
{

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
