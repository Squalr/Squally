#pragma once

#include "Menus/Pause/PauseMenu.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class ClickableTextNode;
class ConfirmationMenu;
class LocalizedLabel;
class LocalizedString;

class IngameMenu : public PauseMenu
{
public:
	static IngameMenu* create();

	void setInventoryClickCallback(std::function<void()> inventoryClickCallback);
	void setPartyClickCallback(std::function<void()> partyClickCallback);
	void setCardsClickCallback(std::function<void()> cardsClickCallback);
	void setCollectablesClickCallback(std::function<void()> collectablesClickCallback);

protected:
	IngameMenu();
	virtual ~IngameMenu();

private:
	typedef PauseMenu super;
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	ClickableTextNode* buildButton(std::string spriteResource, std::string spriteResourceSelected, LocalizedString* text, bool isLeftAligned,  cocos2d::Vec2 offset);

	ClickableTextNode* inventoryButton;
	ClickableTextNode* partyButton;
	ClickableTextNode* cardsButton;
	ClickableTextNode* collectablesButton;

	std::function<void()> inventoryClickCallback;
	std::function<void()> partyClickCallback;
	std::function<void()> cardsClickCallback;
	std::function<void()> collectablesClickCallback;
};
