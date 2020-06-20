#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class InversionGenericPreview : public HackablePreview
{
public:
	static InversionGenericPreview* create();

	HackablePreview* clone() override;

protected:
	InversionGenericPreview();
	virtual ~InversionGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
