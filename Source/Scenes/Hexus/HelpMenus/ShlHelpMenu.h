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

protected:
	ShlHelpMenu();
	virtual ~ShlHelpMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	void resetAnimation();
	void runAnimationLoop();

	LocalizedLabel* description = nullptr;
	Card* rolCard = nullptr;
	ToggleCard* previewCard = nullptr;
	cocos2d::Sprite* attackFrame = nullptr;
	LocalizedLabel* newZero = nullptr;
	LocalizedLabel* animatedLabel = nullptr;
	ConstantString* animatedLabelValue = nullptr;
};
