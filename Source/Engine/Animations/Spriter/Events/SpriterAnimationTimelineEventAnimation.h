#pragma once
#include "base/CCValue.h"

#include "Engine/Animations/Spriter/Events/SpriterAnimationTimelineEventBase.h"

class SpriterAnimationTimeline;

class SpriterAnimationTimelineEventAnimation : public SpriterAnimationTimelineEventBase
{
public:
	static SpriterAnimationTimelineEventAnimation* create(
		SpriterAnimationTimeline* timeline,
		float keyTime,
		float endTime,
		const SpriterTimeline& keyParent,
		const SpriterTimelineKey& animationKey
	);

	int getPartHash();
	const std::string& getPartName();
	int getTimelineKeyId() const;
	float getTimelineKeyTime() const;
	SpriterAnimationTimelineEventAnimation* getNext();
	void setNext(SpriterAnimationTimelineEventAnimation* next);
	void setSamplingWindow(float sampleStartTime, float sampleEndTime, float animationLength, bool sampleTimeWraps);
	bool canAdvance();
	void advance(SpriterAnimationNode* animation) override;
	void applyCurrentState(SpriterAnimationNode* animation);
	void cascade(SpriterAnimationTimelineEventAnimation* parent = nullptr);
	void computeDeltas();
	void addCascadeChild(SpriterAnimationTimelineEventAnimation* cascadeChild);
	void clearCascadeChildren();

protected:
	SpriterAnimationTimelineEventAnimation(SpriterAnimationTimeline* timeline,
		float keyTime,
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
	int timelineKeyId = -1;
	int spin = 0;
	float speed = 0.0f;
	float timelineKeyTime = 0.0f;
	float sampleStartTime = 0.0f;
	float sampleEndTime = 0.0f;
	float animationLength = 0.0f;
	
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
	bool sampleTimeWraps = false;
};
