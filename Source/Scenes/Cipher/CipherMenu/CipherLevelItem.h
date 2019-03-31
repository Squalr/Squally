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
class CipherLevelItem;
class ClickableNode;

class CipherLevelItem : public SmartNode
{
public:
	static CipherLevelItem* create(std::string description, std::string mapFile, int index, std::function<void(CipherLevelItem*)> onMouseOver);
	void initializePositions();

	ClickableNode* startButton;

	std::string tutorialDescription;
	std::string tutorialMapFile;

	const int MaxEntriesPerRow = 5;
	const int MaxEntriesPerPage = CipherLevelItem::MaxEntriesPerRow * 2;

protected:
	CipherLevelItem(std::string description, std::string mapFile, int index, std::function<void(CipherLevelItem*)> onMouseOver);
	~CipherLevelItem();

private:
	typedef SmartNode super;
	void onTutorialClick();
	void onTutorialMouseOver();

	std::function<void(CipherLevelItem*)> onMouseOverEvent;
	bool isLevelComplete;
	int levelIndex;

	cocos2d::Sprite* frame;
};
