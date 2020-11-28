#pragma once
#include "cocos/base/CCValue.h"

#include "Engine/SmartNode.h"

#include "Engine/Animations/Spriter/SpriterStructs.h"

class SpriterAnimationNode;

class SpriterAnimationTimelineEventBase : public SmartNode
{
public:
	void reset();
	virtual void advance(float elapsedTime);

protected:
	SpriterAnimationTimelineEventBase(float startTime, float endTime);

	void onEnter() override;

	virtual void onFire() = 0;

	SpriterCurveType curveType;

private:
	typedef SmartNode super;

	float startTime;
	float endTime;
	bool hasFired;
};
