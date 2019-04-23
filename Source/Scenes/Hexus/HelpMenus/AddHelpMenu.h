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

class AddHelpMenu : public SmartNode
{
public:
	static AddHelpMenu* create();

	void open();

private:
	typedef SmartNode super;
	AddHelpMenu();
	~AddHelpMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void resetAnimation();
	void runAnimationLoop();
	void runCarryLoop(int currentResultValue, int carry);

	LocalizedLabel* description;
	Card* addCard;
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
	LocalizedLabel* decimalOverflowSubtraction;
};
