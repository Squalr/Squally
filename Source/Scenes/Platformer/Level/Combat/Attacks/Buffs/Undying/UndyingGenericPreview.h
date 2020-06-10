#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class UndyingGenericPreview : public HackablePreview
{
public:
	static UndyingGenericPreview* create();

	HackablePreview* clone() override;

protected:
	UndyingGenericPreview();
	virtual ~UndyingGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* healEffect;
};
