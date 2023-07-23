#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class BloodBoilGenericPreview : public HackablePreview
{
public:
	static BloodBoilGenericPreview* create();

	HackablePreview* clone() override;

protected:
	BloodBoilGenericPreview();
	virtual ~BloodBoilGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
