#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;
class SmartAnimationSequenceNode;

class WoodenSpikesUpdateTimerPreview : public HackablePreview
{
public:
	static WoodenSpikesUpdateTimerPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	WoodenSpikesUpdateTimerPreview();
	~WoodenSpikesUpdateTimerPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	SmartAnimationSequenceNode* previewSpikes;
};
