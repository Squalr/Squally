#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class ManaLifeGenericPreview : public HackablePreview
{
public:
	static ManaLifeGenericPreview* create();

	HackablePreview* clone() override;

protected:
	ManaLifeGenericPreview();
	virtual ~ManaLifeGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
