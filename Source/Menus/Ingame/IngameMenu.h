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
	void setMapClickCallback(std::function<void()> mapClickCallback);
	void setCollectablesClickCallback(std::function<void()> collectablesClickCallback);

protected:
	IngameMenu();
	~IngameMenu();

private:
	typedef PauseMenu super;
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	ClickableTextNode* buildButton(std::string spriteResource, std::string spriteResourceSelected, LocalizedString* text, bool isLeftAligned,  cocos2d::Vec2 offset);

	ClickableTextNode* inventoryButton;
	ClickableTextNode* partyButton;
	ClickableTextNode* mapButton;
	ClickableTextNode* collectablesButton;

	std::function<void()> inventoryClickCallback;
	std::function<void()> partyClickCallback;
	std::function<void()> mapClickCallback;
	std::function<void()> collectablesClickCallback;
};
