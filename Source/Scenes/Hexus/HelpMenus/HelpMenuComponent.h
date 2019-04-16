#pragma once

#include "Scenes/Hexus/Components/ComponentBase.h"

namespace cocos2d
{
	class Sprite;
}

class BinDecHexHelpMenu;
class Card;
class ClickableNode;

class HelpMenuComponent : public ComponentBase
{
public:
	static HelpMenuComponent* create();

	void openMenu(Card* card);
	void setExitCallback(std::function<void()> onExit);

protected:
	HelpMenuComponent();
	~HelpMenuComponent();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef ComponentBase super;

	cocos2d::Sprite* background;
	BinDecHexHelpMenu* binDecHexHelpMenu;
	ClickableNode* exitButton;
	std::function<void()> onExit;
};
