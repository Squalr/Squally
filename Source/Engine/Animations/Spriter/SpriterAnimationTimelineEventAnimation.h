#pragma once
#include "cocos/base/CCValue.h"

#include "Engine/Animations/Spriter/SpriterAnimationTimelineEventBase.h"

class SpriterAnimationTimelineEventMainline;

class SpriterAnimationTimelineEventAnimation : public SpriterAnimationTimelineEventBase
{
public:

	static SpriterAnimationTimelineEventAnimation* create(SpriterAnimationNode* animations, const SpriterAnimation& animationData);

protected:
	SpriterAnimationTimelineEventAnimation(SpriterAnimationNode* animations, const SpriterAnimation& animationData);

	void onEnter() override;
	void update(float dt);
	
	virtual void advance(float elapsedTime);
	void onFire() override;

	SpriterAnimation animationData;

private:
	typedef SpriterAnimationTimelineEventBase super;

	std::vector<SpriterAnimationTimelineEventMainline*> mainlineEvents;
	
	float elapsedTime;
	float speed;
};
