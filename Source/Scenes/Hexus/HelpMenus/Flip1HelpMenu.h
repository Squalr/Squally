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

class Flip1HelpMenu : public SmartNode
{
public:
	static Flip1HelpMenu* create();

	void open();

protected:
	Flip1HelpMenu();
	virtual ~Flip1HelpMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	void resetAnimation();
	void runAnimationLoop();

	LocalizedLabel* description = nullptr;
	Card* flip1Card = nullptr;
	ToggleCard* previewCard = nullptr;
	cocos2d::Sprite* attackFrame = nullptr;
	LocalizedLabel* animatedLabel = nullptr;
	ConstantString* animatedLabelValue = nullptr;
};
