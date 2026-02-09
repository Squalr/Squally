#pragma once
#include "cocos/base/CCValue.h"

#include "Engine/SmartNode.h"

class SpriterAnimationPart : public SmartNode
{
public:
	void addAnimationPartChild(SpriterAnimationPart* part);
	void clearAnimationPartChildren();
	void setTimelineCanUpdate(bool canUpdate);
	bool canTimelineUpdate() const;
	void setAnimationOffset(const cocos2d::Vec2& offset);
	const cocos2d::Vec2& getAnimationOffset() const;
	void setAlphaOverride(float alphaOverride);
	float getAlphaOverride() const;
	void setOpacity(GLubyte opacity) override;

protected:
	friend class SpriterAnimationTimeline;
	friend class SpriterAnimationTimelineEventMainline;

	SpriterAnimationPart();
	virtual ~SpriterAnimationPart();
	
	SpriterAnimationPart* parentPart = nullptr;
	std::vector<SpriterAnimationPart*> childAnimationParts;
	
private:
	typedef SmartNode super;

	bool timelineCanUpdate = true;
	cocos2d::Vec2 animationOffset = cocos2d::Vec2::ZERO;
	float alphaOverride = -1.0f;
};
