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
	ShlHelpMenu* shlHelpMenu;
	ShrHelpMenu* shrHelpMenu;

	std::function<void()> onExit;
};
