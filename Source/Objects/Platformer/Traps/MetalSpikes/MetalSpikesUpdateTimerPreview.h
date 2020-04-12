#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;
class SmartAnimationSequenceNode;

class MetalSpikesUpdateTimerPreview : public HackablePreview
{
public:
	static MetalSpikesUpdateTimerPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	MetalSpikesUpdateTimerPreview();
	virtual	~MetalSpikesUpdateTimerPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	SmartAnimationSequenceNode* previewSpikes;
};
