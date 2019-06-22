#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;
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
	cocos2d::Sprite* rewardsMenu;
	LocalizedLabel* victoryLabel;
	LocalizedLabel* itemsFoundLabel;
	ClickableTextNode* returnButton;
};
