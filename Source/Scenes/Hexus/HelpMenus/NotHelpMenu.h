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

class NotHelpMenu : public SmartNode
{
public:
	static NotHelpMenu* create();

	void open();

private:
	typedef SmartNode super;
	NotHelpMenu();
	~NotHelpMenu();

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
