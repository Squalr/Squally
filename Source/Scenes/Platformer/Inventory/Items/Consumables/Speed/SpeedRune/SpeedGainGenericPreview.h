#pragma once

#include "Engine/Hackables/HackablePreview.h"

class SmartAnimationSequenceNode;

class SpeedGainGenericPreview : public HackablePreview
{
public:
	static SpeedGainGenericPreview* create();

	HackablePreview* clone() override;

protected:
	SpeedGainGenericPreview();
	virtual ~SpeedGainGenericPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* healEffect;
};
