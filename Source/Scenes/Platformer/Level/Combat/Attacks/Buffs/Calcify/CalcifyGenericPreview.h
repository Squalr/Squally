#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class CalcifyGenericPreview : public HackablePreview
{
public:
	static CalcifyGenericPreview* create();

	HackablePreview* clone() override;

protected:
	CalcifyGenericPreview();
	virtual ~CalcifyGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
