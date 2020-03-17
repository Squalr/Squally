#pragma once

#include "Engine/Hackables/HackablePreview.h"

class SmartAnimationSequenceNode;

class IncrementHealthGenericPreview : public HackablePreview
{
public:
	static IncrementHealthGenericPreview* create();

	HackablePreview* clone() override;

protected:
	IncrementHealthGenericPreview();
	virtual ~IncrementHealthGenericPreview();
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* healEffect;
};
