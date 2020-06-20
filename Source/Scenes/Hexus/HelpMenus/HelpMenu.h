#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class LayerColor;
	class Sprite;
}

class AddHelpMenu;
class AndHelpMenu;
class BinDecHexHelpMenu;
class CardData;
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

class HelpMenu : public SmartNode
{
public:
	static HelpMenu* create();

	void openMenu(CardData* cardData, bool showBackdrop = false, std::function<void()> onExitSecondary = nullptr);
	void setExitCallback(std::function<void()> onExit);

protected:
	HelpMenu();
	virtual ~HelpMenu();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef SmartNode super;

	cocos2d::LayerColor* backdrop;
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
	std::function<void()> onExitSecondary;
};
