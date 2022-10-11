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

	bool isLaunching = false;
	float launchCountDown = 0.0f;

	cocos2d::Sprite* ballLeft = nullptr;
	cocos2d::Sprite* ballRight = nullptr;
	SmartAnimationSequenceNode* electricityAnimation = nullptr;
};
