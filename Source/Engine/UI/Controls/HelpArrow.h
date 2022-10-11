#pragma once
#include "Engine/SmartNode.h"

class SmartAnimationNode;

class HelpArrow : public SmartNode
{
public:
	static HelpArrow* create();

	void showPointer();
	void hidePointer();

protected:
	HelpArrow();
	virtual ~HelpArrow();

private:
	typedef SmartNode super;

	void onEnter() override;

	SmartAnimationNode* arrow = nullptr;
};
