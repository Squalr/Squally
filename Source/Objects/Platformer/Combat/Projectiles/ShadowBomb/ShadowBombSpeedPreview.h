#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class LocalizedLabel;
class SmartAnimationSequenceNode;

class ShadowBombSpeedPreview : public HackablePreview
{
public:
	static ShadowBombSpeedPreview* create();

	HackablePreview* clone() override;

protected:
	ShadowBombSpeedPreview();
	virtual ~ShadowBombSpeedPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* shadowBomb;
	LocalizedLabel* xmm1Left;
	LocalizedLabel* xmm1Right;
};
