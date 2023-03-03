#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class EnchantmentGenericPreview : public HackablePreview
{
public:
	static EnchantmentGenericPreview* create();

	HackablePreview* clone() override;

protected:
	EnchantmentGenericPreview();
	virtual ~EnchantmentGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
