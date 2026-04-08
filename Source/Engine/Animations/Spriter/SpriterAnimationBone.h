#pragma once

#include "Engine/Animations/Spriter/SpriterAnimationPart.h"

class SpriterAnimationBone : public SpriterAnimationPart
{
public:
	static SpriterAnimationBone* create(cocos2d::CSize boneSize);

	void setDebugDrawHeirarchyDepth(int heirarchyDepth);

protected:
	SpriterAnimationBone(cocos2d::CSize boneSize);
	virtual ~SpriterAnimationBone();

private:
	typedef SpriterAnimationPart super;

	cocos2d::CSize boneSize;
};
