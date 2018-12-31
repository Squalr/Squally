#pragma once

#include "Engine/SmartNode.h"

class SmartAnimationSequenceNode;

class Lightning : public SmartNode
{
public:
	static Lightning* create();

private:
	typedef SmartNode super;
	Lightning();
	~Lightning();

	void onEnter() override;
	void playNextAnimation();

	SmartAnimationSequenceNode* animations;
	bool firstRun;
};

