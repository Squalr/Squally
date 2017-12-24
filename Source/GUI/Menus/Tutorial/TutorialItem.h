#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Components/MenuSprite.h"
#include "Level/Level.h"
#include "Utils/Utils.h"

using namespace cocos2d;

class TutorialItem : public Node
{
public:
	static TutorialItem * create(std::string description, std::string mapFile, int index, std::function<void(TutorialItem*)> onMouseOver);
	void InitializePositions();

	MenuSprite* startButton;

	std::string tutorialDescription;
	std::string tutorialMapFile;

	const int MaxEntriesPerRow = 5;
	const int MaxEntriesPerPage = TutorialItem::MaxEntriesPerRow * 2;

protected:
	TutorialItem(std::string description, std::string mapFile, int index, std::function<void(TutorialItem*)> onMouseOver);
	~TutorialItem();

private:
	void OnTutorialClick(MenuSprite* tutorialItem);
	void OnTutorialMouseOver(MenuSprite* tutorialItem);

	std::function<void(TutorialItem*)> onMouseOverEvent;
	bool isLevelComplete;
	int levelIndex;
	int page;

	Sprite* frame;
	Label* indexLabel;
};
