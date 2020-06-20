#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class HealthLinkGenericPreview : public HackablePreview
{
public:
	static HealthLinkGenericPreview* create();

	HackablePreview* clone() override;

protected:
	HealthLinkGenericPreview();
	virtual ~HealthLinkGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* healEffect;
};
