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

protected:
	Flip4HelpMenu();
	virtual ~Flip4HelpMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	void resetAnimation();
	void runAnimationLoop();

	LocalizedLabel* description = nullptr;
	Card* flip4Card = nullptr;
	ToggleCard* previewCard = nullptr;
	cocos2d::Sprite* attackFrame = nullptr;
	LocalizedLabel* animatedLabel = nullptr;
	ConstantString* animatedLabelValue = nullptr;
};
