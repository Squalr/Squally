#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class ThickHideGenericPreview : public HackablePreview
{
public:
	static ThickHideGenericPreview* create();

	HackablePreview* clone() override;

protected:
	ThickHideGenericPreview();
	virtual ~ThickHideGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
