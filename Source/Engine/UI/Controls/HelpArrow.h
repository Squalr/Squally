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
	typedef SmartNode super;
	HelpArrow();
	virtual ~HelpArrow();

	void onEnter() override;

	SmartAnimationNode* arrow;
};
