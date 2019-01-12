#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;

class SpikeLogSetRotation : public HackablePreview
{
public:
	static SpikeLogSetRotation* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	SpikeLogSetRotation();
	~SpikeLogSetRotation() = default;
	void onEnter() override;
	void initializePositions() override;

	cocos2d::Sprite* previewHeavenHug100;
	cocos2d::Sprite* previewHeavenHug200;
	cocos2d::Sprite* previewHeavenHug400;
	LocalizedLabel* eax100Height;
	LocalizedLabel* eax200Height;
	LocalizedLabel* eax400Height;
};
