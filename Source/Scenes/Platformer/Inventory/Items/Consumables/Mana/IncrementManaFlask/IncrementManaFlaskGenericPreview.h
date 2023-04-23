#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class IncrementManaGenericPreview : public HackablePreview
{
public:
	static IncrementManaGenericPreview* create();

	HackablePreview* clone() override;

protected:
	IncrementManaGenericPreview();
	virtual ~IncrementManaGenericPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* healEffect = nullptr;
};
