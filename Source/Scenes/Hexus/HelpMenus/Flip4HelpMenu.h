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

class Flip4HelpMenu : public SmartNode
{
public:
	static Flip4HelpMenu* create();

	void open();

private:
	typedef SmartNode super;
	Flip4HelpMenu();
	~Flip4HelpMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void resetAnimation();
	void runAnimationLoop();

	LocalizedLabel* description;
	Card* flip4Card;
	ToggleCard* previewCard;
	cocos2d::Sprite* attackFrame;
	LocalizedLabel* animatedLabel;
	ConstantString* animatedLabelValue;
};
