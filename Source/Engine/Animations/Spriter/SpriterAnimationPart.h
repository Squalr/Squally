#pragma once
#include "cocos/base/CCValue.h"

#include "Engine/SmartNode.h"

class SpriterAnimationPart : public SmartNode
{
public:
	void addAnimationPartChild(SpriterAnimationPart* part);
	void clearAnimationPartChildren();

protected:
	friend class SpriterAnimationTimeline;
	friend class SpriterAnimationTimelineEventMainline;

	SpriterAnimationPart();
	virtual ~SpriterAnimationPart();
	
	cocos2d::Vec2 heirarchyScale;
	
private:
	typedef SmartNode super;

	std::vector<SpriterAnimationPart*> childAnimationParts;
};
