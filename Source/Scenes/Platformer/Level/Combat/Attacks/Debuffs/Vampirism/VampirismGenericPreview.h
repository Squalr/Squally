#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class VampirismGenericPreview : public HackablePreview
{
public:
	static VampirismGenericPreview* create();

	HackablePreview* clone() override;

protected:
	VampirismGenericPreview();
	virtual ~VampirismGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
