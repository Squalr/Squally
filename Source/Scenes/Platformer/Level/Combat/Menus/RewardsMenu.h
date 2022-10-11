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

	Timeline* timelineRef = nullptr;
	cocos2d::Sprite* victoryMenu = nullptr;
	cocos2d::Node* expNode = nullptr;
	LocalizedLabel* victoryLabel = nullptr;
	LocalizedLabel* itemsFoundLabel = nullptr;
	ClickableTextNode* returnButton = nullptr;
	Sound* victorySound = nullptr;
	int emblemCount = 0;
};
