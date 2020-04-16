#pragma once

#include "Scenes/MapBase.h"

class AlchemyMenu;
class BlacksmithingMenu;
class Cipher;
class ClickableTextNode;
class CollectablesMenu;
class ConfirmationHud;
class GameHud;
class Hexus;
class InventoryMenu;
class CardsMenu;
class NotificationHud;
class PartyMenu;
class PlatformerEnemy;

class PlatformerMap : public MapBase
{
public:
	static PlatformerMap* create(std::string mapResource, std::string transition = "");

	bool loadMap(std::string mapResource) override;
	
	static const std::string TransitionRespawn;

protected:
	PlatformerMap(std::string transition = "");
	virtual ~PlatformerMap();

private:
	typedef MapBase super;
	void initializePositions() override;
	void initializeListeners() override;
	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void onExit() override;

	void warpSquallyToRespawn();

	bool awaitingConfirmationEnd;

	GameHud* gameHud;
	ConfirmationHud* confirmationHud;
	NotificationHud* notificationHud;
	Cipher* cipher;
	Hexus* hexus;
	CollectablesMenu* collectablesMenu;
	CardsMenu* cardsMenu;
	PartyMenu* partyMenu;
	InventoryMenu* inventoryMenu;
	AlchemyMenu* alchemyMenu;
	BlacksmithingMenu* blacksmithingMenu;
	cocos2d::Node* combatFadeInNode;

	std::string transition;
};
