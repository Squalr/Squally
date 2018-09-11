#pragma once
#include "cocos2d.h"
#include "Resources.h"

#include "Events/NavigationEvents.h"
#include "Engine/Rendering/Components/MenuSprite.h"
#include "Scenes/Maps/Platformer/PlatformerMap.h"

using namespace cocos2d;

class HexusOpponentItem : public Node
{
public:
	static HexusOpponentItem * create(std::string description, std::string mapFile, int index, std::function<void(HexusOpponentItem*)> onMouseOver);
	void initializePositions();

	MenuSprite* startButton;

	std::string tutorialDescription;
	std::string tutorialMapFile;

	const int MaxEntriesPerRow = 5;
	const int MaxEntriesPerPage = HexusOpponentItem::MaxEntriesPerRow * 2;

protected:
	HexusOpponentItem(std::string description, std::string mapFile, int index, std::function<void(HexusOpponentItem*)> onMouseOver);
	~HexusOpponentItem();

private:
	void onTutorialClick(MenuSprite* HexusOpponentItem);
	void onTutorialMouseOver(MenuSprite* HexusOpponentItem);

	std::function<void(HexusOpponentItem*)> onMouseOverEvent;
	bool isLevelComplete;
	int levelIndex;
	int page;

	Sprite* frame;
	Label* indexLabel;
};
