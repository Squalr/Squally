#pragma once

#include "Engine/Hackables/HackablePreview.h"

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
	~MetalSpikesUpdateTimerPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	SmartAnimationSequenceNode* previewSpikedLog;
	LocalizedLabel* ecxAnimationCount;
	ConstantString* countString;
};
