#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class PactOfTheAncientsGenericPreview : public HackablePreview
{
public:
	static PactOfTheAncientsGenericPreview* create();

	HackablePreview* clone() override;

protected:
	PactOfTheAncientsGenericPreview();
	virtual ~PactOfTheAncientsGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
