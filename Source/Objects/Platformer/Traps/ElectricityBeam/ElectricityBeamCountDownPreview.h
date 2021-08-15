#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class ConstantString;
class LocalizedLabel;
class SmartAnimationSequenceNode;

class ElectricityBeamCountDownPreview : public HackablePreview
{
public:
	static ElectricityBeamCountDownPreview* create();

	HackablePreview* clone() override;

protected:
	ElectricityBeamCountDownPreview();
	virtual ~ElectricityBeamCountDownPreview();

	void onEnter() override;
	void initializePositions() override;
	void update(float dt) override;

private:
	typedef HackablePreview super;

	bool isLaunching = false;
	float launchCountDown = 0.0f;

	cocos2d::Sprite* ballLeft = nullptr;
	cocos2d::Sprite* ballRight = nullptr;
	SmartAnimationSequenceNode* electricityAnimation = nullptr;
	ConstantString* zbxTimerStr = nullptr;
	LocalizedLabel* zbxTimer = nullptr;
};
