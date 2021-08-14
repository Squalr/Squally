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

class OrHelpMenu : public SmartNode
{
public:
	static OrHelpMenu* create();

	void open();

protected:
	OrHelpMenu();
	virtual ~OrHelpMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	void resetAnimation();
	void runAnimationLoop();

	LocalizedLabel* description = nullptr;
	Card* orCard = nullptr;
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
};
