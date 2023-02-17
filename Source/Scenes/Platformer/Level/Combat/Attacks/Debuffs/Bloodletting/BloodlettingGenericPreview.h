#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class BloodlettingGenericPreview : public HackablePreview
{
public:
	static BloodlettingGenericPreview* create();

	HackablePreview* clone() override;

protected:
	BloodlettingGenericPreview();
	virtual ~BloodlettingGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* healEffect = nullptr;
};
