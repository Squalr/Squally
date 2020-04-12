#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class StoneSkinGenericPreview : public HackablePreview
{
public:
	static StoneSkinGenericPreview* create();

	HackablePreview* clone() override;

protected:
	StoneSkinGenericPreview();
	virtual ~StoneSkinGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
