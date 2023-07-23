#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SpellOfBindingGenericPreview : public HackablePreview
{
public:
	static SpellOfBindingGenericPreview* create();

	HackablePreview* clone() override;

protected:
	SpellOfBindingGenericPreview();
	virtual ~SpellOfBindingGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
