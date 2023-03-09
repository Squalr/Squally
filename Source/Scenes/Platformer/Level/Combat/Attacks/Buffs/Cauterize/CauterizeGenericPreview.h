#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class CauterizeGenericPreview : public HackablePreview
{
public:
	static CauterizeGenericPreview* create();

	HackablePreview* clone() override;

protected:
	CauterizeGenericPreview();
	virtual ~CauterizeGenericPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* healEffect = nullptr;
};
