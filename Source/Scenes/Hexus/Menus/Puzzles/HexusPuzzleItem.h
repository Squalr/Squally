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
class ClickableNode;

class HexusPuzzleItem : public SmartNode
{
public:
	static HexusPuzzleItem* create(std::string description, std::string mapFile, int index, std::function<void(HexusPuzzleItem*)> onMouseOver);
	void initializePositions();

	ClickableNode* startButton;

	std::string tutorialDescription;
	std::string tutorialMapFile;

	const int MaxEntriesPerRow = 5;
	const int MaxEntriesPerPage = HexusPuzzleItem::MaxEntriesPerRow * 2;

protected:
	HexusPuzzleItem(std::string description, std::string mapFile, int index, std::function<void(HexusPuzzleItem*)> onMouseOver);
	~HexusPuzzleItem();

private:
	typedef SmartNode super;
	void onTutorialClick();
	void onTutorialMouseOver();

	std::function<void(HexusPuzzleItem*)> onMouseOverEvent;
	bool isLevelComplete;
	int levelIndex;
	int page;

	cocos2d::Sprite* frame;
	LocalizedLabel* indexLabel;
};
