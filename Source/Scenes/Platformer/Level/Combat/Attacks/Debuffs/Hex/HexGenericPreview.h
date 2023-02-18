#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class HexGenericPreview : public HackablePreview
{
public:
	static HexGenericPreview* create();

	HackablePreview* clone() override;

protected:
	HexGenericPreview();
	virtual ~HexGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
