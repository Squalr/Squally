#pragma once
#include <set>

#include "cocos/base/CCValue.h"

#include "Engine/Animations/Spriter/SpriterStructs.h"
#include "Engine/SmartNode.h"

class SpriterAnimationNode;
class SpriterAnimationTimelineEventAnimation;
class SpriterAnimationTimelineEventMainline;

class SpriterAnimationTimeline : public SmartNode
{
public:
	static SpriterAnimationTimeline* getInstance(const std::string& animationResource);

	void registerAnimationNode(SpriterAnimationNode* animationNode);
	void unregisterAnimationNode(SpriterAnimationNode* animationNode);

protected:
	SpriterAnimationTimeline(const std::string& animationResource);

	void onEnter() override;
	void update(float dt);

	float sampleMainlineCurve(float timeRatio);
	float sampleCurve(float timeRatio, SpriterCurveType curveType, float c1, float c2, float c3, float c4);

	SpriterCurveType curveType;

private:
	typedef SmartNode super;

	void buildTimelines(const SpriterData& spriterData);

	// Animation nodes that will be updated every update tick
	std::set<SpriterAnimationNode*> registeredAnimationNodes;
	
	// Responsible for reparenting, curve sampling, bone heirarchy, and z-sorting
	std::vector<SpriterAnimationTimelineEventMainline*> mainlineEvents;

	// Responsible for object position/scale, and curve sampling overrides
	std::vector<SpriterAnimationTimelineEventAnimation*> animationEvents;

	static std::map<std::string, SpriterAnimationTimeline*> TimelineCache;
};
