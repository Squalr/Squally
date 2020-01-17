#pragma once

#include "Engine/Hackables/HackablePreview.h"

class LocalizedLabel;
class SmartAnimationSequenceNode;

class FireballSpeedPreview : public HackablePreview
{
public:
	static FireballSpeedPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	FireballSpeedPreview();
	virtual ~FireballSpeedPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	SmartAnimationSequenceNode* fireball;
	LocalizedLabel* xmm1Left;
	LocalizedLabel* xmm1Right;
};
