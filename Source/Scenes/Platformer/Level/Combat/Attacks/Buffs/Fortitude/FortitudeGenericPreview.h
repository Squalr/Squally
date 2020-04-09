#pragma once

#include "Engine/Hackables/HackablePreview.h"

class SmartAnimationSequenceNode;

class FortitudeGenericPreview : public HackablePreview
{
public:
	static FortitudeGenericPreview* create();

	HackablePreview* clone() override;

protected:
	FortitudeGenericPreview();
	virtual ~FortitudeGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* healEffect;
};
