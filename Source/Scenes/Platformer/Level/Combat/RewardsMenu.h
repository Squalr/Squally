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

private:
	typedef SmartNode super;
	RewardsMenu();
	virtual ~RewardsMenu() = default;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void loadRewards();

	cocos2d::Sprite* rewardsMenu;
	LocalizedLabel* titleLabel;
	ScrollPane* rewardsScroll;
	ClickableTextNode* okayButton;
};
