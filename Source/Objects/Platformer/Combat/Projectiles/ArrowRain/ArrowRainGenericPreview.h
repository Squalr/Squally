#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class ArrowRainGenericPreview : public HackablePreview
{
public:
	static ArrowRainGenericPreview* create();

	HackablePreview* clone() override;

protected:
	ArrowRainGenericPreview();
	virtual ~ArrowRainGenericPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* fireball;
};
