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

class MovHelpMenu : public SmartNode
{
public:
	static MovHelpMenu* create();

	void open();

protected:
	MovHelpMenu();
	virtual ~MovHelpMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;
	void resetAnimation();
	void runAnimationLoop();

	LocalizedLabel* description;
	Card* movCard;
	ToggleCard* previewCardA;
	ToggleCard* previewCardB;
	cocos2d::Sprite* attackFrameA;
	cocos2d::Sprite* attackFrameB;
	LocalizedLabel* animatedLabelA;
	ConstantString* animatedLabelAValue;
	LocalizedLabel* animatedLabelB;
	ConstantString* animatedLabelBValue;
};
