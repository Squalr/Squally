#pragma once

#include "Engine/Hackables/HackablePreview.h"

class SmartAnimationSequenceNode;

class LesserStrengthGenericPreview : public HackablePreview
{
public:
	static LesserStrengthGenericPreview* create();

	HackablePreview* clone() override;

protected:
	LesserStrengthGenericPreview();
	virtual ~LesserStrengthGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* healEffect;
};
