#pragma once

#include "Engine/Hackables/HackablePreview.h"

class SmartAnimationSequenceNode;

class TrainingHealGenericPreview : public HackablePreview
{
public:
	static TrainingHealGenericPreview* create();

	HackablePreview* clone() override;

protected:
	TrainingHealGenericPreview();
	virtual ~TrainingHealGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* healEffect;
};
