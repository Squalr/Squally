#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class AddHealthGenericPreview : public HackablePreview
{
public:
	static AddHealthGenericPreview* create();

	HackablePreview* clone() override;

protected:
	AddHealthGenericPreview();
	virtual ~AddHealthGenericPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* healEffect = nullptr;
};
