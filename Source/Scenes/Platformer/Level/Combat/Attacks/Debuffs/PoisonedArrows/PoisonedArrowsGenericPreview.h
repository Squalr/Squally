#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class PoisonedArrowsGenericPreview : public HackablePreview
{
public:
	static PoisonedArrowsGenericPreview* create();

	HackablePreview* clone() override;

protected:
	PoisonedArrowsGenericPreview();
	virtual ~PoisonedArrowsGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* healEffect = nullptr;
};
