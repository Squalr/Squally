#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class CurseOfTonguesGenericPreview : public HackablePreview
{
public:
	static CurseOfTonguesGenericPreview* create();

	HackablePreview* clone() override;

protected:
	CurseOfTonguesGenericPreview();
	virtual ~CurseOfTonguesGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* healEffect;
};
