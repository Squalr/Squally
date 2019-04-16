#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Node;
}

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

	cocos2d::Node* binCardNode;
	cocos2d::Node* decCardNode;
	cocos2d::Node* hexCardNode;
	Card* binCard;
	Card* decCard;
	Card* hexCard;
	LocalizedLabel* equalsLabelLeft;
	LocalizedLabel* equalsLabelRight;
	LocalizedLabel* binHeader;
	LocalizedLabel* decHeader;
	LocalizedLabel* hexHeader;
};
