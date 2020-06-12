#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class LocalizedLabel;
class SmartAnimationSequenceNode;

class ArrowRainSpeedPreview : public HackablePreview
{
public:
	static ArrowRainSpeedPreview* create();

	HackablePreview* clone() override;

protected:
	ArrowRainSpeedPreview();
	virtual ~ArrowRainSpeedPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* fireball;
	LocalizedLabel* xmm1Left;
	LocalizedLabel* xmm1Right;
};
