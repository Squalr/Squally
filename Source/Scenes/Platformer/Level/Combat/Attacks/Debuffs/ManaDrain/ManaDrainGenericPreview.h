#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class ManaDrainGenericPreview : public HackablePreview
{
public:
	static ManaDrainGenericPreview* create();

	HackablePreview* clone() override;

protected:
	ManaDrainGenericPreview();
	virtual ~ManaDrainGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* healEffect;
};
