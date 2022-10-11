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

class XorHelpMenu : public SmartNode
{
public:
	static XorHelpMenu* create();

	void open();

protected:
	XorHelpMenu();
	virtual ~XorHelpMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;
	
	void resetAnimation();
	void runAnimationLoop();

	LocalizedLabel* description = nullptr;
	Card* xorCard = nullptr;
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
