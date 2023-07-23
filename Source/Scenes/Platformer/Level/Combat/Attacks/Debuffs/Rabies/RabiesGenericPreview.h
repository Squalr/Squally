#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class RabiesGenericPreview : public HackablePreview
{
public:
	static RabiesGenericPreview* create();

	HackablePreview* clone() override;

protected:
	RabiesGenericPreview();
	virtual ~RabiesGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
