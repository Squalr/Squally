#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class RegenerationGenericPreview : public HackablePreview
{
public:
	static RegenerationGenericPreview* create();

	HackablePreview* clone() override;

protected:
	RegenerationGenericPreview();
	virtual ~RegenerationGenericPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* healEffect;
};
