#pragma once
#include "cocos/base/CCValue.h"

#include "Engine/Animations/Spriter/Events/SpriterAnimationTimelineEventBase.h"

class SpriterAnimationTimelineEventMainline : public SpriterAnimationTimelineEventBase
{
public:
	static SpriterAnimationTimelineEventMainline* create(SpriterAnimationTimeline* timeline, float endTime, const SpriterMainlineKey& mainlineKey);

protected:
	SpriterAnimationTimelineEventMainline(SpriterAnimationTimeline* timeline, float endTime, const SpriterMainlineKey& mainlineKey);

	void onEnter() override;
	void onFire(SpriterAnimationNode* animation) override;

private:
	typedef SpriterAnimationTimelineEventBase super;

	std::map<int, int> boneParentTable;
	std::map<int, int> objectParentTable;
};
