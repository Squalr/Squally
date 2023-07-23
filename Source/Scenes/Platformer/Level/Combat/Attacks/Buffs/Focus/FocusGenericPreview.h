#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class FocusGenericPreview : public HackablePreview
{
public:
	static FocusGenericPreview* create();

	HackablePreview* clone() override;

protected:
	FocusGenericPreview();
	virtual ~FocusGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
