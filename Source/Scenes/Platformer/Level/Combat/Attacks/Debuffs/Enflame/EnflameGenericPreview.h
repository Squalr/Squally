#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class EnflameGenericPreview : public HackablePreview
{
public:
	static EnflameGenericPreview* create();

	HackablePreview* clone() override;

protected:
	EnflameGenericPreview();
	virtual ~EnflameGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* healEffect = nullptr;
};
