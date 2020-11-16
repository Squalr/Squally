#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;
class LocalizedLabel;
class Sound;
class Timeline;

class RewardsMenu : public SmartNode
{
public:
	static RewardsMenu* create(Timeline* timelineRef);

	void show();

protected:
	RewardsMenu(Timeline* timelineRef);
	virtual ~RewardsMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;
	void giveExp();
	void loadRewards();
	void clearEmblems();
	void addExpEmblem(std::string emblemResource, int gain);

	Timeline* timelineRef;

	cocos2d::Sprite* victoryMenu;
	cocos2d::Node* expNode;
	LocalizedLabel* victoryLabel;
	LocalizedLabel* itemsFoundLabel;
	ClickableTextNode* returnButton;
	Sound* victorySound;
	int emblemCount;
};
