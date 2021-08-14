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

protected:
	AddHelpMenu();
	virtual ~AddHelpMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	void resetAnimation();
	void runAnimationLoop();
	void runCarryLoop(int currentResultValue, int carry);

	LocalizedLabel* description = nullptr;
	Card* addCard = nullptr;
	ToggleCard* previewCardA = nullptr;
	ToggleCard* previewCardB = nullptr;
	cocos2d::Sprite* attackFrameA = nullptr;
	cocos2d::Sprite* attackFrameB = nullptr;
	cocos2d::Sprite* attackFrameC = nullptr;
	LocalizedLabel* animatedLabelA = nullptr;
	ConstantString* animatedLabelAValue = nullptr;
	LocalizedLabel* animatedLabelB = nullptr;
	ConstantString* animatedLabelBValue = nullptr;
	LocalizedLabel* animatedLabelC = nullptr;
	ConstantString* animatedLabelCValue = nullptr;
	LocalizedLabel* carryLabel = nullptr;
	ConstantString* carryLabelValue = nullptr;
	LocalizedLabel* decimalOverflowSubtraction = nullptr;
};
