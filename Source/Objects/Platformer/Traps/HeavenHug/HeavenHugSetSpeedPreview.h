#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

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

protected:
	HeavenHugSetSpeedPreview();
	virtual ~HeavenHugSetSpeedPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	cocos2d::Sprite* previewHeavenHug100 = nullptr;
	cocos2d::Sprite* previewHeavenHug200 = nullptr;
	cocos2d::Sprite* previewHeavenHug400 = nullptr;
	LocalizedLabel* eax100Height = nullptr;
	LocalizedLabel* eax200Height = nullptr;
	LocalizedLabel* eax400Height = nullptr;
};
