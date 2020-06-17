#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class ConstantString;
class LocalizedLabel;
class SmartAnimationSequenceNode;

class ElectricityBeamGenericPreview : public HackablePreview
{
public:
	static ElectricityBeamGenericPreview* create();

	HackablePreview* clone() override;

protected:
	ElectricityBeamGenericPreview();
	virtual ~ElectricityBeamGenericPreview();

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
};
