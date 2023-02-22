#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class InnerFireGenericPreview : public HackablePreview
{
public:
	static InnerFireGenericPreview* create();

	HackablePreview* clone() override;

protected:
	InnerFireGenericPreview();
	virtual ~InnerFireGenericPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* healEffect = nullptr;
};
