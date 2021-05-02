#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class CurseOfTheAncientsGenericPreview : public HackablePreview
{
public:
	static CurseOfTheAncientsGenericPreview* create();

	HackablePreview* clone() override;

protected:
	CurseOfTheAncientsGenericPreview();
	virtual ~CurseOfTheAncientsGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
