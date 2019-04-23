#pragma once

#include "Scenes/Hexus/Components/ComponentBase.h"

namespace cocos2d
{
	class LayerColor;
	class Sprite;
}

class AddHelpMenu;
class AndHelpMenu;
class BinDecHexHelpMenu;
class Card;
class ClickableNode;
class Flip1HelpMenu;
class Flip2HelpMenu;
class Flip3HelpMenu;
class Flip4HelpMenu;
class MovHelpMenu;
class NotHelpMenu;
class OrHelpMenu;
class RolHelpMenu;
class RorHelpMenu;
class ShlHelpMenu;
class ShrHelpMenu;
class SubHelpMenu;
class XorHelpMenu;

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
	ClickableNode* exitButton;
	AddHelpMenu* addHelpMenu;
	AndHelpMenu* andHelpMenu;
	BinDecHexHelpMenu* binDecHexHelpMenu;
	Flip1HelpMenu* flip1HelpMenu;
	Flip2HelpMenu* flip2HelpMenu;
	Flip3HelpMenu* flip3HelpMenu;
	Flip4HelpMenu* flip4HelpMenu;
	NotHelpMenu* notHelpMenu;
	MovHelpMenu* movHelpMenu;
	OrHelpMenu* orHelpMenu;
	RolHelpMenu* rolHelpMenu;
	RorHelpMenu* rorHelpMenu;
	ShlHelpMenu* shlHelpMenu;
	ShrHelpMenu* shrHelpMenu;
	SubHelpMenu* subHelpMenu;
	XorHelpMenu* xorHelpMenu;

	std::function<void()> onExit;
};
