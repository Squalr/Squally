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

protected:
	SubHelpMenu();
	virtual ~SubHelpMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	void resetAnimation();
	void runAnimationLoop();
	void runTrivialSubtraction(std::function<void()> callback);
	void runCarryLoop();

	LocalizedLabel* description = nullptr;
	Card* subCard = nullptr;
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
	LocalizedLabel* decimalUnderflowAddition = nullptr;

	std::string tempTopString;
	std::string tempCarryString;
};
