#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;
class LocalizedLabel;
class PlatformerEntity;

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
	void update(float dt) override;

	cocos2d::Sprite* rewardsMenu;
	cocos2d::Node* rewardsNode;
	LocalizedLabel* windowTitle;
	ClickableTextNode* okayButton;
};
