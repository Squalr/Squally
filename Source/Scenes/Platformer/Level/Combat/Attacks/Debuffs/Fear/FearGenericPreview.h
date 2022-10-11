#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class FearGenericPreview : public HackablePreview
{
public:
	static FearGenericPreview* create();

	HackablePreview* clone() override;

protected:
	FearGenericPreview();
	virtual ~FearGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* healEffect = nullptr;
};
