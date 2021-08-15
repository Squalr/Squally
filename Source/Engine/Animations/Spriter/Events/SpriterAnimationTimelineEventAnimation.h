#pragma once
#include "cocos/base/CCValue.h"

#include "Engine/Animations/Spriter/Events/SpriterAnimationTimelineEventBase.h"

class SpriterAnimationTimeline;

class SpriterAnimationTimelineEventAnimation : public SpriterAnimationTimelineEventBase
{
public:
	static SpriterAnimationTimelineEventAnimation* create(
		SpriterAnimationTimeline* timeline,
		float endTime,
		const SpriterTimeline& keyParent,
		const SpriterTimelineKey& animationKey
	);

	int getPartHash();
	const std::string& getPartName();
	SpriterAnimationTimelineEventAnimation* getNext();
	void setNext(SpriterAnimationTimelineEventAnimation* next);
	bool canAdvance();
	void advance(SpriterAnimationNode* animation) override;
	void cascade(SpriterAnimationTimelineEventAnimation* parent = nullptr);
	void computeDeltas();
	void addCascadeChild(SpriterAnimationTimelineEventAnimation* cascadeChild);
	void clearCascadeChildren();

protected:
	SpriterAnimationTimelineEventAnimation(SpriterAnimationTimeline* timeline,
		float endTime,
		const SpriterTimeline& keyParent,
		const SpriterTimelineKey& animationKey
	);
	
	void onFire(SpriterAnimationNode* animation) override;

	SpriterAnimationTimelineEventAnimation* next = nullptr;

private:
	typedef SpriterAnimationTimelineEventBase super;
	
	std::string partName;
	int partHash = 0;
	int spin = 0;
	float speed = 0.0f;
	
	cocos2d::Vec2 position = cocos2d::Vec2::ZERO;
	cocos2d::Vec2 anchor = cocos2d::Vec2::ZERO;
	cocos2d::Vec2 scale = cocos2d::Vec2::ZERO;
	float rotation = 0.0f;
	float alpha = 0.0f;

	cocos2d::Vec2 deltaPosition;
	cocos2d::Vec2 deltaAnchor;
	cocos2d::Vec2 deltaScale;
	float deltaRotation = 0.0f;
	float deltaAlpha = 0.0f;

	std::vector<SpriterAnimationTimelineEventAnimation*> cascadeChildren;

	bool isBone = false;
	bool hasNoAnimationChanges = false;
};
