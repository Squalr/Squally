#pragma once
#include "cocos/base/CCValue.h"

#include "Engine/Animations/Spriter/SpriterStructs.h"
#include "Engine/SmartNode.h"

class SpriterAnimationNode;

class SpriterAnimationTimelineEventBase : public SmartNode
{
public:
	virtual void advance(float elapsedTime);

protected:
	SpriterAnimationTimelineEventBase(SpriterAnimationNode* animations, float startTime, float endTime);

	void onEnter() override;

	virtual void onFire() = 0;

	std::vector<SpriterAnimationTimelineEventBase*> childTimelineEvents;
	SpriterAnimationNode* animations;

	SpriterCurveType curveType;

private:
	typedef SmartNode super;

	SpriterData spriterData;
	float startTime;
	float endTime;
	bool hasFired;
};
