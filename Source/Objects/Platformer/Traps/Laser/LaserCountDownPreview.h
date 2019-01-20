#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;
class SmartAnimationSequenceNode;

class LaserCountDownPreview : public HackablePreview
{
public:
	static LaserCountDownPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	LaserCountDownPreview();
	~LaserCountDownPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	SmartAnimationSequenceNode* previewSpikes;
};
