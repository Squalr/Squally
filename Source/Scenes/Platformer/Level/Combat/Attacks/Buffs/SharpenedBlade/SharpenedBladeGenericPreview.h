#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class SharpenedBladeGenericPreview : public HackablePreview
{
public:
	static SharpenedBladeGenericPreview* create();

	HackablePreview* clone() override;

protected:
	SharpenedBladeGenericPreview();
	virtual ~SharpenedBladeGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
