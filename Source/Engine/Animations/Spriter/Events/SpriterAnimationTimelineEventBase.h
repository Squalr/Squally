#pragma once
#include "cocos/base/CCValue.h"

#include "Engine/SmartNode.h"

#include "Engine/Animations/Spriter/SpriterStructs.h"

class SpriterAnimationNode;
class SpriterAnimationTimeline;

class SpriterAnimationTimelineEventBase : public SmartNode
{
public:
	virtual void advance(SpriterAnimationNode* animation);

protected:
	SpriterAnimationTimelineEventBase(SpriterAnimationTimeline* timeline, float startTime, float endTime, SpriterCurveType curveType, float c1, float c2, float c3, float c4);

	void onEnter() override;

	virtual void onFire(SpriterAnimationNode* animation) = 0;

	SpriterAnimationTimeline* timeline;

private:
	typedef SmartNode super;
	
	float startTime;
	float endTime;
	SpriterCurveType curveType;
	float c1;
	float c2;
	float c3;
	float c4;
};
