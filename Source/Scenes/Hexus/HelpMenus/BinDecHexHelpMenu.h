#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Node;
}

class ToggleCard;
class CardData;
class LocalizedLabel;

class BinDecHexHelpMenu : public SmartNode
{
public:
	static BinDecHexHelpMenu* create();

	void open(CardData* cardData);

protected:
	BinDecHexHelpMenu();
	virtual ~BinDecHexHelpMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	LocalizedLabel* description = nullptr;
	ToggleCard* binCard = nullptr;
	ToggleCard* decCard = nullptr;
	ToggleCard* hexCard = nullptr;
	LocalizedLabel* equalsLabelLeft = nullptr;
	LocalizedLabel* equalsLabelRight = nullptr;
	LocalizedLabel* binHeader = nullptr;
	LocalizedLabel* decHeader = nullptr;
	LocalizedLabel* hexHeader = nullptr;
};
