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
	void initializeListeners() override;

private:
	typedef SmartNode super;

	cocos2d::LayerColor* backdrop = nullptr;
	cocos2d::Sprite* background = nullptr;
	cocos2d::LayerColor* textPanel = nullptr;
	ClickableNode* exitButton = nullptr;
	AddHelpMenu* addHelpMenu = nullptr;
	AndHelpMenu* andHelpMenu = nullptr;
	BinDecHexHelpMenu* binDecHexHelpMenu = nullptr;
	Flip1HelpMenu* flip1HelpMenu = nullptr;
	Flip2HelpMenu* flip2HelpMenu = nullptr;
	Flip3HelpMenu* flip3HelpMenu = nullptr;
	Flip4HelpMenu* flip4HelpMenu = nullptr;
	NotHelpMenu* notHelpMenu = nullptr;
	MovHelpMenu* movHelpMenu = nullptr;
	OrHelpMenu* orHelpMenu = nullptr;
	RolHelpMenu* rolHelpMenu = nullptr;
	RorHelpMenu* rorHelpMenu = nullptr;
	ShlHelpMenu* shlHelpMenu = nullptr;
	ShrHelpMenu* shrHelpMenu = nullptr;
	SubHelpMenu* subHelpMenu = nullptr;
	XorHelpMenu* xorHelpMenu = nullptr;

	std::function<void()> onExit = nullptr;
	std::function<void()> onExitSecondary = nullptr;
};
