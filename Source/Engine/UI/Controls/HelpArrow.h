#pragma once
#include "cocos2d.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/SmartNode.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

class HelpArrow : public SmartNode
{
public:
	static HelpArrow * create();

	void showPointer();
	void hidePointer();

private:
	HelpArrow();
	~HelpArrow();

	void onEnter() override;

	SmartAnimationNode* arrow;
};
