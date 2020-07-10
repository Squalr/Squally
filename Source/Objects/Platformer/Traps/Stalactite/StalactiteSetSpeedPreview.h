#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;

class StalactiteSetSpeedPreview : public HackablePreview
{
public:
	static StalactiteSetSpeedPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	StalactiteSetSpeedPreview();
	virtual ~StalactiteSetSpeedPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	cocos2d::Sprite* previewStalactite100;
	cocos2d::Sprite* previewStalactite200;
	cocos2d::Sprite* previewStalactite400;
	LocalizedLabel* eax100Height;
	LocalizedLabel* eax200Height;
	LocalizedLabel* eax400Height;
};
