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

class ShrHelpMenu : public SmartNode
{
public:
	static ShrHelpMenu* create();

	void open();

private:
	typedef SmartNode super;
	ShrHelpMenu();
	~ShrHelpMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void resetAnimation();
	void runAnimationLoop();

	LocalizedLabel* description;
	Card* shrCard;
	ToggleCard* previewCard;
	cocos2d::Sprite* attackFrame;
	LocalizedLabel* newZero;
	LocalizedLabel* animatedLabel;
	ConstantString* animatedLabelValue;
};
