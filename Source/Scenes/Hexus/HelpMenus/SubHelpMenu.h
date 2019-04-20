#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class DrawNode;
	class Node;
	class Sprite;
}

class Card;
class ConstantString;
class LocalizedLabel;
class ToggleCard;

class SubHelpMenu : public SmartNode
{
public:
	static SubHelpMenu* create();

	void open();

private:
	typedef SmartNode super;
	SubHelpMenu();
	~SubHelpMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void resetAnimation();
	void runAnimationLoop();
	void runTrivialSubtraction();
	void runCarryLoop();

	LocalizedLabel* description;
	Card* subCard;
	ToggleCard* previewCardA;
	ToggleCard* previewCardB;
	cocos2d::Sprite* attackFrameA;
	cocos2d::Sprite* attackFrameB;
	cocos2d::Sprite* attackFrameC;
	LocalizedLabel* animatedLabelA;
	ConstantString* animatedLabelAValue;
	LocalizedLabel* animatedLabelB;
	ConstantString* animatedLabelBValue;
	LocalizedLabel* animatedLabelC;
	ConstantString* animatedLabelCValue;
	LocalizedLabel* carryLabel;
	ConstantString* carryLabelValue;
	LocalizedLabel* decimalUnderflowAddition;
};
