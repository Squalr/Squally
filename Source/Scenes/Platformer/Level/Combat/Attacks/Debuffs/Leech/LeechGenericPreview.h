#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class LeechGenericPreview : public HackablePreview
{
public:
	static LeechGenericPreview* create();

	HackablePreview* clone() override;

protected:
	LeechGenericPreview();
	virtual ~LeechGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
