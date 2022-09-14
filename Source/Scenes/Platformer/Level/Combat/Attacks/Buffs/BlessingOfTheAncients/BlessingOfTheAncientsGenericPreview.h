#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class BlessingOfTheAncientsGenericPreview : public HackablePreview
{
public:
	static BlessingOfTheAncientsGenericPreview* create();

	HackablePreview* clone() override;

protected:
	BlessingOfTheAncientsGenericPreview();
	virtual ~BlessingOfTheAncientsGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
