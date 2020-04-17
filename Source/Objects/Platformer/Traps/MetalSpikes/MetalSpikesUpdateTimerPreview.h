#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class ConstantString;
class LocalizedLabel;
class SmartAnimationSequenceNode;

class MetalSpikesUpdateTimerPreview : public HackablePreview
{
public:
	static MetalSpikesUpdateTimerPreview* create();

	HackablePreview* clone() override;

protected:
	MetalSpikesUpdateTimerPreview();
	virtual ~MetalSpikesUpdateTimerPreview();

	void onEnter() override;
	void initializePositions() override;
	void update(float dt) override;

private:
	typedef HackablePreview super;

	bool isLaunching;
	float launchCountDown;

	SmartAnimationSequenceNode* previewSpikes;
	
	ConstantString* xmm2TimerStr;
	LocalizedLabel* xmm2Timer;
};
