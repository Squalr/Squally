#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class HeavyBladeGenericPreview : public HackablePreview
{
public:
	static HeavyBladeGenericPreview* create();

	HackablePreview* clone() override;

protected:
	HeavyBladeGenericPreview();
	virtual ~HeavyBladeGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
