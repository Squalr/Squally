#pragma once

#include "Menus/Tutorials/TutorialTabBase.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;
class LocalizedLabel;
class PlatformerEntity;
class ScrollPane;
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
