#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class LocalizedLabel;
class SmartAnimationSequenceNode;

class WaterballSpeedPreview : public HackablePreview
{
public:
	static WaterballSpeedPreview* create();

	HackablePreview* clone() override;

protected:
	WaterballSpeedPreview();
	virtual ~WaterballSpeedPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* waterball = nullptr;
	LocalizedLabel* xmm1Left = nullptr;
	LocalizedLabel* xmm1Right = nullptr;
};
