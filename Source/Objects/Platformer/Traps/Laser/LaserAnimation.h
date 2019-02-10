#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class LaserAnimation : public SmartNode
{
public:
	static LaserAnimation* create(float height);

	void runAnimation(std::function<void()> onBeamActiveCallback = nullptr, std::function<void()> onBeamDeactiveCallback = nullptr);

private:
	typedef SmartNode super;
	LaserAnimation(float height);
	virtual	~LaserAnimation();

	void onEnter() override;
	void initializePositions() override;

	cocos2d::Sprite* laserHeadTop;
	cocos2d::Sprite* laserHeadBottom;
	cocos2d::Sprite* laserWeak;
	cocos2d::Sprite* laserStrong;

	float height;
};
