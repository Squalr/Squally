#pragma once

#include "Engine/SmartNode.h"

class Card;

class BinDecHexHelpMenu : public SmartNode
{
public:
	static BinDecHexHelpMenu* create();

private:
	typedef SmartNode super;
	BinDecHexHelpMenu();
	~BinDecHexHelpMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	Card* binCard;
	Card* decCard;
	Card* hexCard;
};
