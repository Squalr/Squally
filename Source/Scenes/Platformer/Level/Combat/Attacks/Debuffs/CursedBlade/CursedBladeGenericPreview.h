#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class CursedBladeGenericPreview : public HackablePreview
{
public:
	static CursedBladeGenericPreview* create();

	HackablePreview* clone() override;

protected:
	CursedBladeGenericPreview();
	virtual ~CursedBladeGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
