#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class DiseasedGenericPreview : public HackablePreview
{
public:
	static DiseasedGenericPreview* create();

	HackablePreview* clone() override;

protected:
	DiseasedGenericPreview();
	virtual ~DiseasedGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
