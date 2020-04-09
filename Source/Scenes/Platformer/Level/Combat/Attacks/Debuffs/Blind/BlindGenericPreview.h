#pragma once

#include "Engine/Hackables/HackablePreview.h"

class SmartAnimationSequenceNode;

class BlindGenericPreview : public HackablePreview
{
public:
	static BlindGenericPreview* create();

	HackablePreview* clone() override;

protected:
	BlindGenericPreview();
	virtual ~BlindGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* healEffect;
};
