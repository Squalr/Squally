#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Node;
}

class AutoCard;
class Card;
class LocalizedLabel;

class BinDecHexHelpMenu : public SmartNode
{
public:
	static BinDecHexHelpMenu* create();

	void open(Card* card);

private:
	typedef SmartNode super;
	BinDecHexHelpMenu();
	~BinDecHexHelpMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	AutoCard* binCard;
	AutoCard* decCard;
	AutoCard* hexCard;
	LocalizedLabel* equalsLabelLeft;
	LocalizedLabel* equalsLabelRight;
	LocalizedLabel* binHeader;
	LocalizedLabel* decHeader;
	LocalizedLabel* hexHeader;
};
