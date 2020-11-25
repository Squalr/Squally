#pragma once

#include "Menus/Pause/PauseMenu.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;
class LocalizedString;

class PlatformerPauseMenu : public PauseMenu
{
public:
	static PlatformerPauseMenu* create();

	void disableInventory();
	void disableCards();
	void disableCollectables();
	void setInventoryClickCallback(std::function<void()> inventoryClickCallback);
	void setPartyClickCallback(std::function<void()> partyClickCallback);
	void setCardsClickCallback(std::function<void()> cardsClickCallback);
	void setCollectablesClickCallback(std::function<void()> collectablesClickCallback);

protected:
	PlatformerPauseMenu();
	virtual ~PlatformerPauseMenu();
	
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef PauseMenu super;

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
