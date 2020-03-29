#pragma once

#include "Engine/Hackables/HackablePreview.h"

class SmartAnimationSequenceNode;

class SiphonLifeGenericPreview : public HackablePreview
{
public:
	static SiphonLifeGenericPreview* create();

	HackablePreview* clone() override;

protected:
	SiphonLifeGenericPreview();
	virtual ~SiphonLifeGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* healEffect;
};
