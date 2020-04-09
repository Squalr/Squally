#pragma once

#include "Engine/Hackables/HackablePreview.h"

class LocalizedLabel;
class SmartAnimationSequenceNode;

class FireballSpeedPreview : public HackablePreview
{
public:
	static FireballSpeedPreview* create();

	HackablePreview* clone() override;

protected:
	FireballSpeedPreview();
	virtual ~FireballSpeedPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* fireball;
	LocalizedLabel* xmm1Left;
	LocalizedLabel* xmm1Right;
};
