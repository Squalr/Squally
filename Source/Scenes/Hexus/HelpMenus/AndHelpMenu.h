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

class AndHelpMenu : public SmartNode
{
public:
	static AndHelpMenu* create();

	void open();

private:
	typedef SmartNode super;
	AndHelpMenu();
	~AndHelpMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void resetAnimation();
	void runAnimationLoop();

	LocalizedLabel* description;
	Card* notCard;
	ToggleCard* previewCard;
	cocos2d::Sprite* attackFrame;
	LocalizedLabel* animatedLabel;
	ConstantString* animatedLabelValue;
};
