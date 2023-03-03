#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class ChanceGenericPreview : public HackablePreview
{
public:
	static ChanceGenericPreview* create();

	HackablePreview* clone() override;

protected:
	ChanceGenericPreview();
	virtual ~ChanceGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
