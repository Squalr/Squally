#pragma once
#include "cocos/base/CCValue.h"

#include "Engine/Animations/Spriter/Events/SpriterAnimationTimelineEventBase.h"

class SpriterAnimationPart;

class SpriterAnimationTimelineEventMainline : public SpriterAnimationTimelineEventBase
{
public:
	static SpriterAnimationTimelineEventMainline* create(SpriterAnimationTimeline* timeline, float endTime, const SpriterAnimation& animation, const SpriterMainlineKey& mainlineKey);

protected:
	SpriterAnimationTimelineEventMainline(SpriterAnimationTimeline* timeline, float endTime, const SpriterAnimation& animation, const SpriterMainlineKey& mainlineKey);

	void onEnter() override;
	void onFire(SpriterAnimationNode* animation) override;

private:
	typedef SpriterAnimationTimelineEventBase super;

	int getBoneDepth(int boneId);

	std::map<int, int> boneParentTable;
	std::map<int, int> objectParentTable;
	std::map<int, std::string> boneNameMap;
	std::map<int, std::string> objectNameMap;
	std::map<std::string, int> boneIdMap;
	std::map<std::string, int> objectIdMap;
	std::map<std::string, int> objectZMap;
};
