#pragma once

#include "Scenes/MapBase.h"

class AlchemyMenu;
class BlacksmithingMenu;
class Cipher;
class ClickableTextNode;
class CollectablesMenu;
class ConfirmationHud;
class GameHud;
class HelpMenu;
class Hexus;
class InventoryMenu;
class ItemInfoMenu;
class CardsMenu;
class NotificationHud;
class PartyMenu;
class PlatformerEnemy;
class MiniMap;

class PlatformerMap : public MapBase
{
public:
	static PlatformerMap* create(std::string mapResource, std::string transition = "");

	bool loadMap(std::string mapResource) override;
	
	static const std::string TransitionRespawn;

protected:
	PlatformerMap(std::string transition = "");
	virtual ~PlatformerMap();
	
	void initializePositions() override;
	void initializeListeners() override;
	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void onExit() override;

private:
	typedef MapBase super;

	void warpSquallyToRespawn();
	void buildHexus();
	void buildCardsMenu();
	void buildHexusCardHelp();
	void buildItemInfoMenu();
	void buildCipher();

	bool awaitingConfirmationEnd;

	GameHud* gameHud;
	ConfirmationHud* confirmationHud;
	NotificationHud* notificationHud;
	Cipher* cipher;
	Hexus* hexus;
	HelpMenu* cardHelpMenu;
	CollectablesMenu* collectablesMenu;
	ItemInfoMenu* itemInfoMenu;
	CardsMenu* cardsMenu;
	PartyMenu* partyMenu;
	InventoryMenu* inventoryMenu;
	AlchemyMenu* alchemyMenu;
	BlacksmithingMenu* blacksmithingMenu;
	cocos2d::Node* combatFadeInNode;
	MiniMap* miniMap;

	std::string transition;
};
