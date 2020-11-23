#pragma once
#include "cocos/base/CCValue.h"

#include "Engine/Animations/Spriter/SpriterAnimationTimelineEventBase.h"

class SpriterAnimationTimelineEventMainline : public SpriterAnimationTimelineEventBase
{
public:
	static SpriterAnimationTimelineEventMainline* create(SpriterAnimationNode* animations, const SpriterMainlineKey& mainlineData, float endTime);

	float SampleMainlineCurve(float timeRatio);
	float SampleCurve(float timeRatio, SpriterCurveType curveType, float c1, float c2, float c3, float c4);
	SpriterCurveType getCurveType();

protected:
	SpriterAnimationTimelineEventMainline(SpriterAnimationNode* animations, const SpriterMainlineKey& mainlineData, float endTime);

	void onEnter() override;
	void onFire() override;

	SpriterMainlineKey mainlineData;

private:
	typedef SpriterAnimationTimelineEventBase super;
};
