#pragma once
#include "cocos2d.h"
#include "Resources.h"

#include "Events/NavigationEvents.h"
#include "Engine/Rendering/Components/MenuSprite.h"
#include "Scenes/Maps/Platformer/PlatformerMap.h"

using namespace cocos2d;

class TutorialItem : public Node
{
public:
	static TutorialItem * create(std::string description, std::string mapFile, int index, std::function<void(TutorialItem*)> onMouseOver);
	void initializePositions();

	MenuSprite* startButton;

	std::string tutorialDescription;
	std::string tutorialMapFile;

	const int MaxEntriesPerRow = 5;
	const int MaxEntriesPerPage = TutorialItem::MaxEntriesPerRow * 2;

protected:
	TutorialItem(std::string description, std::string mapFile, int index, std::function<void(TutorialItem*)> onMouseOver);
	~TutorialItem();

private:
	void onTutorialClick(MenuSprite* tutorialItem);
	void onTutorialMouseOver(MenuSprite* tutorialItem);

	std::function<void(TutorialItem*)> onMouseOverEvent;
	bool isLevelComplete;
	int levelIndex;
	int page;

	Sprite* frame;
	Label* indexLabel;
};
