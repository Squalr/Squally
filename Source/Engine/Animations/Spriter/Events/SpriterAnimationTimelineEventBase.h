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

	float getKeyTime();
	float getEndTime();

protected:
	SpriterAnimationTimelineEventBase(SpriterAnimationTimeline* timeline, float keytime, float endTime, SpriterCurveType curveType, float c1, float c2, float c3, float c4);
	
	virtual void onFire(SpriterAnimationNode* animation) = 0;

	SpriterAnimationTimeline* timeline = nullptr;
	float keytime = 0.0f;
	float endTime = 0.0f;
	SpriterCurveType curveType;
	float c1 = 0.0f;
	float c2 = 0.0f;
	float c3 = 0.0f;
	float c4 = 0.0f;

private:
	typedef SmartNode super;
};
