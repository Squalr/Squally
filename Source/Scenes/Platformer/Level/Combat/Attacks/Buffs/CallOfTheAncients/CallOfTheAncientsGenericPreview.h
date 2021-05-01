#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class CallOfTheAncientsGenericPreview : public HackablePreview
{
public:
	static CallOfTheAncientsGenericPreview* create();

	HackablePreview* clone() override;

protected:
	CallOfTheAncientsGenericPreview();
	virtual ~CallOfTheAncientsGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
