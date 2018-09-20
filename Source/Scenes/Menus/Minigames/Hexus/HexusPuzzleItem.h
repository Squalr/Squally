#pragma once
#include "cocos2d.h"
#include "Resources.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Events/HexusEvents.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Maps/Platformer/PlatformerMap.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Deck.h"

using namespace cocos2d;

class HexusPuzzleItem : public Node
{
public:
	static HexusPuzzleItem * create(std::string description, std::string mapFile, int index, std::function<void(HexusPuzzleItem*)> onMouseOver);
	void initializePositions();

	MenuSprite* startButton;

	std::string tutorialDescription;
	std::string tutorialMapFile;

	const int MaxEntriesPerRow = 5;
	const int MaxEntriesPerPage = HexusPuzzleItem::MaxEntriesPerRow * 2;

protected:
	HexusPuzzleItem(std::string description, std::string mapFile, int index, std::function<void(HexusPuzzleItem*)> onMouseOver);
	~HexusPuzzleItem();

private:
	void onTutorialClick(MenuSprite* HexusPuzzleItem);
	void onTutorialMouseOver(MenuSprite* HexusPuzzleItem);

	std::function<void(HexusPuzzleItem*)> onMouseOverEvent;
	bool isLevelComplete;
	int levelIndex;
	int page;

	Sprite* frame;
	Label* indexLabel;
};
