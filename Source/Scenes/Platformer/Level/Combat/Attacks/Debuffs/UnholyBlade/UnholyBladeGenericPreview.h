#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class UnholyBladeGenericPreview : public HackablePreview
{
public:
	static UnholyBladeGenericPreview* create();

	HackablePreview* clone() override;

protected:
	UnholyBladeGenericPreview();
	virtual ~UnholyBladeGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
