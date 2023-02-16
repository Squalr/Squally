#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class ImmortalityGenericPreview : public HackablePreview
{
public:
	static ImmortalityGenericPreview* create();

	HackablePreview* clone() override;

protected:
	ImmortalityGenericPreview();
	virtual ~ImmortalityGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
