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

	/*
	const cocos2d::Vec2& getBoneScale() const;
    void setScaleX(float scaleX) override;
    void setScaleY(float scaleY) override;
	*/
	void setDebugDrawHeirarchyDepth(int heirarchyDepth);

protected:
	SpriterAnimationBone(cocos2d::Size boneSize);
	virtual ~SpriterAnimationBone();

	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;

private:
	typedef SmartNode super;

	void redrawDebugDraw();

	cocos2d::Size boneSize;
	cocos2d::Vec2 boneScale;
	cocos2d::DrawNode* debugDraw;
	int heirarchyDepth;
	
	static const std::vector<cocos2d::Color4F> DebugColorHeirarchy;
};
