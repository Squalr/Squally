#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class HasteGenericPreview : public HackablePreview
{
public:
	static HasteGenericPreview* create();

	HackablePreview* clone() override;

protected:
	HasteGenericPreview();
	virtual ~HasteGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
