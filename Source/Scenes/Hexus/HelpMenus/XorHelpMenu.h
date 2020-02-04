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

	LocalizedLabel* description;
	Card* xorCard;
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
};
