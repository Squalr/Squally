#pragma once

#include "Menus/Tutorials/TutorialTabBase.h"

class TutorialEntry;

class HexEditingTab : public TutorialTabBase
{
public:
	static HexEditingTab* create();

protected:
	HexEditingTab();
	virtual ~HexEditingTab();

	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;

private:
	typedef TutorialTabBase super;

	void loadHexEditingGoldTutorial();

	TutorialEntry* hexEditingGold;
	
	cocos2d::Node* shopkeeper;
};
