#pragma once

#include "Engine/SmartNode.h"

class SmartAnimationSequenceNode;

class LightningSphere : public SmartNode
{
public:
	static LightningSphere* create();

private:
	typedef SmartNode super;
	LightningSphere();
	~LightningSphere();

	void onEnter() override;
	void playNextAnimation();

	SmartAnimationSequenceNode* animations;
};

