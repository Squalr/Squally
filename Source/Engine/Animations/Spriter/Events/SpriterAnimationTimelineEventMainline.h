#pragma once
#include "cocos/base/CCValue.h"

#include "Engine/Animations/Spriter/Events/SpriterAnimationTimelineEventBase.h"

class SpriterAnimationTimelineEventMainline : public SpriterAnimationTimelineEventBase
{
public:
	static SpriterAnimationTimelineEventMainline* create(const SpriterMainlineKey& mainlineData, float endTime);

	SpriterCurveType getCurveType();

protected:
	SpriterAnimationTimelineEventMainline(const SpriterMainlineKey& mainlineData, float endTime);

	void onEnter() override;
	void onFire() override;

	SpriterMainlineKey mainlineData;

private:
	typedef SpriterAnimationTimelineEventBase super;
};
