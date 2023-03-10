#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class MeltGenericPreview : public HackablePreview
{
public:
	static MeltGenericPreview* create();

	HackablePreview* clone() override;

protected:
	MeltGenericPreview();
	virtual ~MeltGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
