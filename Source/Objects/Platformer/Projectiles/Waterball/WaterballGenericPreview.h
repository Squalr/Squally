#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class WaterballGenericPreview : public HackablePreview
{
public:
	static WaterballGenericPreview* create();

	HackablePreview* clone() override;

protected:
	WaterballGenericPreview();
	virtual ~WaterballGenericPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* waterball = nullptr;
};
