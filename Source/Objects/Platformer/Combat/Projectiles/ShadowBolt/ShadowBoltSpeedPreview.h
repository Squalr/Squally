#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class LocalizedLabel;
class SmartAnimationSequenceNode;

class ShadowBoltSpeedPreview : public HackablePreview
{
public:
	static ShadowBoltSpeedPreview* create();

	HackablePreview* clone() override;

protected:
	ShadowBoltSpeedPreview();
	virtual ~ShadowBoltSpeedPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* shadowBolt = nullptr;
	LocalizedLabel* xmm1Left = nullptr;
	LocalizedLabel* xmm1Right = nullptr;
};
