#pragma once

#include "Engine/Animations/Spriter/SpriterAnimationPart.h"

namespace cocos2d
{
	class DrawNode;
};

class SpriterAnimationBone : public SpriterAnimationPart
{
public:
	static SpriterAnimationBone* create(cocos2d::CSize boneSize);
	
	void setDebugDrawHeirarchyDepth(int heirarchyDepth);

protected:
	SpriterAnimationBone(cocos2d::CSize boneSize);
	virtual ~SpriterAnimationBone();

	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;

private:
	typedef SpriterAnimationPart super;

	void redrawDebugDraw();

	float boneRotation = 0.0f;
	cocos2d::CSize boneSize;
	cocos2d::DrawNode* debugDraw = nullptr;
	int heirarchyDepth = 0;
	
	static const std::vector<cocos2d::Color4F> DebugColorHeirarchy;
};
