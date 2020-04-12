#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class EnrageGenericPreview : public HackablePreview
{
public:
	static EnrageGenericPreview* create();

	HackablePreview* clone() override;

protected:
	EnrageGenericPreview();
	virtual ~EnrageGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* healEffect;
};
