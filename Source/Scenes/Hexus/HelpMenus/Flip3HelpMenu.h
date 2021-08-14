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

class Flip3HelpMenu : public SmartNode
{
public:
	static Flip3HelpMenu* create();

	void open();

protected:
	Flip3HelpMenu();
	virtual ~Flip3HelpMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;
	void resetAnimation();
	void runAnimationLoop();

	LocalizedLabel* description = nullptr;
	Card* flip3Card = nullptr;
	ToggleCard* previewCard = nullptr;
	cocos2d::Sprite* attackFrame = nullptr;
	LocalizedLabel* animatedLabel = nullptr;
	ConstantString* animatedLabelValue = nullptr;
};
