#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class RadiationGenericPreview : public HackablePreview
{
public:
	static RadiationGenericPreview* create();

	HackablePreview* clone() override;

protected:
	RadiationGenericPreview();
	virtual ~RadiationGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* healEffect = nullptr;
};
