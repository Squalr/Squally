#pragma once

#include "Scenes/MapBase.h"

namespace cocos2d
{
	namespace cocos_experimental
	{
		class TMXTiledMap;
	}
}

class AlchemyMenu;
class BlacksmithingMenu;
class CardsMenu;
class Cipher;
class CollectablesMenu;
class ConfirmationHud;
class PlatformerPauseMenu;
class GameHud;
class HelpMenu;
class Hexus;
class InventoryMenu;
class ItemInfoMenu;
template <class T>
class LazyNode;
class NotificationHud;
class PartyMenu;
class MiniMap;

class PlatformerMap : public MapBase
{
public:
	static PlatformerMap* create(std::string transition = "");
	
	static const std::string TransitionRespawn;

protected:
	PlatformerMap(std::string transition = "");
	virtual ~PlatformerMap();
	
	void initializePositions() override;
	void initializeListeners() override;
	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void onExit() override;
	bool loadMapFromTmx(std::string mapResource, cocos2d::cocos_experimental::TMXTiledMap* mapRaw) override;
	void openPauseMenu(cocos2d::Node* refocusTarget) override;

private:
	typedef MapBase super;

	void warpSquallyToRespawn();
	void loadMiniMap(std::string mapResource, cocos2d::cocos_experimental::TMXTiledMap* mapRaw);

	// Lazy initializers
	Cipher* buildCipher();
	Hexus* buildHexus();
	HelpMenu* buildHexusCardHelpMenu();
	CollectablesMenu* buildCollectablesMenu();
	ItemInfoMenu* buildItemInfoMenu();
	CardsMenu* buildCardsMenu();
	PartyMenu* buildPartyMenu();
	InventoryMenu* buildInventoryMenu();
	AlchemyMenu* buildAlchemyMenu();
	BlacksmithingMenu* buildBlacksmithingMenu();
	PlatformerPauseMenu* buildPlatformerPauseMenu();

	bool awaitingConfirmationEnd;

	GameHud* gameHud;
	ConfirmationHud* confirmationHud;
	NotificationHud* notificationHud;
	LazyNode<Cipher>* cipher;
	LazyNode<Hexus>* hexus;
	LazyNode<HelpMenu>* cardHelpMenu;
	LazyNode<CollectablesMenu>* collectablesMenu;
	LazyNode<ItemInfoMenu>* itemInfoMenu;
	LazyNode<CardsMenu>* cardsMenu;
	LazyNode<PartyMenu>* partyMenu;
	LazyNode<InventoryMenu>* inventoryMenu;
	LazyNode<AlchemyMenu>* alchemyMenu;
	LazyNode<BlacksmithingMenu>* blacksmithingMenu;
	cocos2d::Node* combatFadeInNode;
	LazyNode<PlatformerPauseMenu>* platformerPauseMenu;
	MiniMap* miniMap;

	std::string transition;
};
