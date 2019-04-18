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

class ShlHelpMenu : public SmartNode
{
public:
	static ShlHelpMenu* create();

	void open();

private:
	typedef SmartNode super;
	ShlHelpMenu();
	~ShlHelpMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void resetAnimation();
	void runAnimationLoop();

	LocalizedLabel* description;
	Card* rolCard;
	ToggleCard* previewCard;
	cocos2d::Sprite* attackFrame;
	LocalizedLabel* newZero;
	LocalizedLabel* animatedLabel;
	ConstantString* animatedLabelValue;
};
