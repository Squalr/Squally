#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class WeaknessGenericPreview : public HackablePreview
{
public:
	static WeaknessGenericPreview* create();

	HackablePreview* clone() override;

protected:
	WeaknessGenericPreview();
	virtual ~WeaknessGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* healEffect;
};
