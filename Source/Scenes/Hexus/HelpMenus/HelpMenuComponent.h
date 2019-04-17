#pragma once

#include "Scenes/Hexus/Components/ComponentBase.h"

namespace cocos2d
{
	class LayerColor;
	class Sprite;
}

class BinDecHexHelpMenu;
class Card;
class ClickableNode;
class Flip1HelpMenu;
class Flip2HelpMenu;
class Flip3HelpMenu;
class Flip4HelpMenu;
class NotHelpMenu;
class RolHelpMenu;
class RorHelpMenu;
class ShlHelpMenu;
class ShrHelpMenu;

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
	cocos2d::LayerColor* textPanel;
	BinDecHexHelpMenu* binDecHexHelpMenu;
	ClickableNode* exitButton;
	Flip1HelpMenu* flip1HelpMenu;
	Flip2HelpMenu* flip2HelpMenu;
	Flip3HelpMenu* flip3HelpMenu;
	Flip4HelpMenu* flip4HelpMenu;
	NotHelpMenu* notHelpMenu;
	RolHelpMenu* rolHelpMenu;
	RorHelpMenu* rorHelpMenu;
	ShlHelpMenu* shlHelpMenu;
	ShrHelpMenu* shrHelpMenu;

	std::function<void()> onExit;
};
