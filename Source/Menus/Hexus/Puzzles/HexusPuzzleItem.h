#pragma once
#include <functional>
#include <string>

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Label;
	class Sprite;
}

class LocalizedLabel;
class HexusPuzzleItem;
class MenuSprite;

class HexusPuzzleItem : public SmartNode
{
public:
	static HexusPuzzleItem* create(std::string description, std::string mapFile, int index, std::function<void(HexusPuzzleItem*)> onMouseOver);
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
	typedef SmartNode super;
	void onTutorialClick(MenuSprite* HexusPuzzleItem);
	void onTutorialMouseOver(MenuSprite* HexusPuzzleItem);

	std::function<void(HexusPuzzleItem*)> onMouseOverEvent;
	bool isLevelComplete;
	int levelIndex;
	int page;

	cocos2d::Sprite* frame;
	LocalizedLabel* indexLabel;
};
