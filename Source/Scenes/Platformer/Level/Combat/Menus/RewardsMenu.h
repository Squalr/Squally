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
class Sound;

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
	void giveExp();
	void loadRewards();
	void clearEmblems();
	void addExpEmblem(std::string emblemResource, int gain);

	cocos2d::Sprite* victoryMenu;
	cocos2d::Node* expNode;
	LocalizedLabel* victoryLabel;
	LocalizedLabel* itemsFoundLabel;
	ClickableTextNode* returnButton;
	Sound* victorySound;
	int emblemCount;
};
