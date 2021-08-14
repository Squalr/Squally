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

class RorHelpMenu : public SmartNode
{
public:
	static RorHelpMenu* create();

	void open();

protected:
	RorHelpMenu();
	virtual ~RorHelpMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	void resetAnimation();
	void runAnimationLoop();

	LocalizedLabel* description = nullptr;
	Card* rorCard = nullptr;
	ToggleCard* previewCard = nullptr;
	cocos2d::Sprite* attackFrame = nullptr;
	LocalizedLabel* animatedLabel = nullptr;
	ConstantString* animatedLabelValue = nullptr;
};
