#pragma once

#include "Engine/SmartNode.h"

class SmartAnimationSequenceNode;

class Lightning : public SmartNode
{
public:
	static Lightning* create();

private:
	Lightning();
	~Lightning();

	void onEnter() override;
	void playNextAnimation();

	SmartAnimationSequenceNode* animations;
	bool firstRun;
};

