#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class ShieldWallGenericPreview : public HackablePreview
{
public:
	static ShieldWallGenericPreview* create();

	HackablePreview* clone() override;

protected:
	ShieldWallGenericPreview();
	virtual ~ShieldWallGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
