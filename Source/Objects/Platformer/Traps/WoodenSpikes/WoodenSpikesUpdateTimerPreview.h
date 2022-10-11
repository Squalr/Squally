#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class ConstantString;
class LocalizedLabel;
class SmartAnimationSequenceNode;

class WoodenSpikesUpdateTimerPreview : public HackablePreview
{
public:
	static WoodenSpikesUpdateTimerPreview* create();

	HackablePreview* clone() override;

protected:
	WoodenSpikesUpdateTimerPreview();
	virtual ~WoodenSpikesUpdateTimerPreview();

	void onEnter() override;
	void initializePositions() override;
	void update(float dt) override;

private:
	typedef HackablePreview super;

	bool isLaunching = false;
	float launchCountDown = 0.0f;

	SmartAnimationSequenceNode* previewSpikes = nullptr;
	ConstantString* ebxTimerStr = nullptr;
	LocalizedLabel* ebxTimer = nullptr;
};
