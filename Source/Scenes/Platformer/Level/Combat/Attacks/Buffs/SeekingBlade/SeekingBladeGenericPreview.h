#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class SeekingBladeGenericPreview : public HackablePreview
{
public:
	static SeekingBladeGenericPreview* create();

	HackablePreview* clone() override;

protected:
	SeekingBladeGenericPreview();
	virtual ~SeekingBladeGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
