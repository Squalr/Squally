#pragma once
#include "cocos/base/CCValue.h"

#include "Engine/SmartNode.h"

class SpriterAnimationPart : public SmartNode
{
public:
	void setRelativePosition(const cocos2d::Vec2& relativePosition);
	void setHeirarchyScale(const cocos2d::Vec2& scale);
	void addAnimationPartChild(SpriterAnimationPart* part);
	void clearAnimationPartChildren();

protected:
	friend class SpriterAnimationTimeline;

	SpriterAnimationPart();
	virtual ~SpriterAnimationPart();

	virtual void cascadeScales(cocos2d::Vec2 scale = cocos2d::Vec2::ONE);
	
	cocos2d::Vec2 heirarchyScale;
	
private:
	typedef SmartNode super;

	std::vector<SpriterAnimationPart*> childAnimationParts;
	cocos2d::Vec2 relativePosition;
};
