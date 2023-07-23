#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class CursedSwingsGenericPreview : public HackablePreview
{
public:
	static CursedSwingsGenericPreview* create();

	HackablePreview* clone() override;

protected:
	CursedSwingsGenericPreview();
	virtual ~CursedSwingsGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
