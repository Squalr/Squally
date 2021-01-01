#pragma once
#include "cocos/base/CCValue.h"

#include "Engine/SmartNode.h"

class SpriterAnimationPart : public SmartNode
{
public:
	int getId() const;

	virtual void setHeirarchyScale(const cocos2d::Vec2& scale);
	cocos2d::Vec2 getHeirarchyScale();
	cocos2d::Vec2 getFullHeirarchyScale();

protected:
	SpriterAnimationPart();
	virtual ~SpriterAnimationPart();
	
private:
	typedef SmartNode super;

	cocos2d::Vec2 heirarchyScale;
};
