#pragma once
#include "Engine/SmartNode.h"

class SmartAnimationNode;

class HelpArrow : public SmartNode
{
public:
	static HelpArrow * create();

	void showPointer();
	void hidePointer();

private:
	HelpArrow();
	virtual ~HelpArrow();

	void onEnter() override;

	SmartAnimationNode* arrow;
};
