#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class ShadowBombGenericPreview : public HackablePreview
{
public:
	static ShadowBombGenericPreview* create();

	HackablePreview* clone() override;

protected:
	ShadowBombGenericPreview();
	virtual ~ShadowBombGenericPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* animationNode = nullptr;
};
