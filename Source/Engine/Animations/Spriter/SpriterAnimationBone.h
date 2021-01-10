#pragma once

#include "Engine/Animations/Spriter/SpriterAnimationPart.h"

namespace cocos2d
{
	class DrawNode;
};

class SpriterAnimationBone : public SpriterAnimationPart
{
public:
	static SpriterAnimationBone* create(cocos2d::Size boneSize);
	
	void setDebugDrawHeirarchyDepth(int heirarchyDepth);

protected:
	SpriterAnimationBone(cocos2d::Size boneSize);
	virtual ~SpriterAnimationBone();

	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;

private:
	typedef SpriterAnimationPart super;

	void redrawDebugDraw();

	float boneRotation;
	cocos2d::Size boneSize;
	cocos2d::DrawNode* debugDraw;
	int heirarchyDepth;
	
	static const std::vector<cocos2d::Color4F> DebugColorHeirarchy;
};
