#pragma once

#include "Engine/Hackables/HackablePreview.h"

class LocalizedLabel;
class SmartAnimationSequenceNode;

class TimeBombSpeedPreview : public HackablePreview
{
public:
	static TimeBombSpeedPreview* create();

	HackablePreview* clone() override;

protected:
	TimeBombSpeedPreview();
	virtual ~TimeBombSpeedPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* fireball;
	LocalizedLabel* xmm1Left;
	LocalizedLabel* xmm1Right;
};
