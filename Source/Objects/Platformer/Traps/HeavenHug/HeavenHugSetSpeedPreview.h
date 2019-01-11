#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;

class HeavenHugSetSpeedPreview : public HackablePreview
{
public:
	static HeavenHugSetSpeedPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	HeavenHugSetSpeedPreview();
	~HeavenHugSetSpeedPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	cocos2d::Sprite* previewHeavenHug;
	LocalizedLabel* eax0Degrees;
	LocalizedLabel* eax90Degrees;
	LocalizedLabel* eax180Degrees;
	LocalizedLabel* eax270Degrees;
};
