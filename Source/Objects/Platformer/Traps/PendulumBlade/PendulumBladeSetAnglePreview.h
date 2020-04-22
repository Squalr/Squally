#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;

class PendulumBladeSetAnglePreview : public HackablePreview
{
public:
	static PendulumBladeSetAnglePreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	PendulumBladeSetAnglePreview();
	virtual ~PendulumBladeSetAnglePreview() = default;
	void onEnter() override;
	void initializePositions() override;

	cocos2d::Sprite* previewBlade;
	LocalizedLabel* eax0Degrees;
	LocalizedLabel* eax90Degrees;
	LocalizedLabel* eax180Degrees;
	LocalizedLabel* eax270Degrees;
};
