#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class StrengthGenericPreview : public HackablePreview
{
public:
	static StrengthGenericPreview* create();

	HackablePreview* clone() override;

protected:
	StrengthGenericPreview();
	virtual ~StrengthGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
