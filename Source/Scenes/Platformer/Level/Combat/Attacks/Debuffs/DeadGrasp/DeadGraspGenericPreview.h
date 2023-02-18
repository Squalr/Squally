#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class DeadGraspGenericPreview : public HackablePreview
{
public:
	static DeadGraspGenericPreview* create();

	HackablePreview* clone() override;

protected:
	DeadGraspGenericPreview();
	virtual ~DeadGraspGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
