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

	bool isLaunching;
	float launchCountDown;

	cocos2d::Sprite* ballLeft;
	cocos2d::Sprite* ballRight;
	SmartAnimationSequenceNode* electricityAnimation;
	
	ConstantString* zbxTimerStr;
	LocalizedLabel* zbxTimer;
};
