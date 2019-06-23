#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;
class ConstantString;
class LocalizedLabel;
class PlatformerEntity;
class ScrollPane;

class RewardsMenu : public SmartNode
{
public:
	static RewardsMenu* create();

	void show();

private:
	typedef SmartNode super;
	RewardsMenu();
	~RewardsMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void loadRewards();

	cocos2d::Sprite* victoryMenu;
	cocos2d::Sprite* expSprite;
	cocos2d::Sprite* goldSprite;
	ConstantString* expValue;
	ConstantString* goldValue;
	LocalizedLabel* expLabel;
	LocalizedLabel* goldLabel;
	LocalizedLabel* victoryLabel;
	LocalizedLabel* itemsFoundLabel;
	ClickableTextNode* returnButton;
};
