#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class EnchantedBladeGenericPreview : public HackablePreview
{
public:
	static EnchantedBladeGenericPreview* create();

	HackablePreview* clone() override;

protected:
	EnchantedBladeGenericPreview();
	virtual ~EnchantedBladeGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
