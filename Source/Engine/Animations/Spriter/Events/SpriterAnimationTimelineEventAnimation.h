#pragma once
#include "cocos/base/CCValue.h"

#include "Engine/Animations/Spriter/Events/SpriterAnimationTimelineEventBase.h"

class SpriterAnimationTimelineEventAnimation : public SpriterAnimationTimelineEventBase
{
public:
	static SpriterAnimationTimelineEventAnimation* create(float startTime, float endTime);

protected:
	SpriterAnimationTimelineEventAnimation(float startTime, float endTime);
	
	virtual void advance(float elapsedTime);
	void onFire() override;

private:
	typedef SpriterAnimationTimelineEventBase super;
	
	float elapsedTime;
	float speed;
};
