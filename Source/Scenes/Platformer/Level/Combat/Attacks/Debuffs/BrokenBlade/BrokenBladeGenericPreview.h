#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class BrokenBladeGenericPreview : public HackablePreview
{
public:
	static BrokenBladeGenericPreview* create();

	HackablePreview* clone() override;

protected:
	BrokenBladeGenericPreview();
	virtual ~BrokenBladeGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* healEffect;
};
