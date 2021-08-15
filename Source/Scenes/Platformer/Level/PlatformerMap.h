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
class DismantleMenu;
class GameHud;
class FadeHud;
class HelpMenu;
class Hexus;
class InventoryMenu;
class ItemInfoMenu;
class PlatformerPauseMenu;
template <class T> class LazyNode;
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
	DismantleMenu* buildDismantleMenu();
	PlatformerPauseMenu* buildPlatformerPauseMenu();

	bool awaitingConfirmationEnd = false;

	GameHud* gameHud = nullptr;
	ConfirmationHud* confirmationHud = nullptr;
	NotificationHud* notificationHud = nullptr;
	LazyNode<Cipher>* cipher = nullptr;
	LazyNode<Hexus>* hexus = nullptr;
	LazyNode<HelpMenu>* cardHelpMenu = nullptr;
	LazyNode<CollectablesMenu>* collectablesMenu = nullptr;
	LazyNode<ItemInfoMenu>* itemInfoMenu = nullptr;
	LazyNode<CardsMenu>* cardsMenu = nullptr;
	LazyNode<PartyMenu>* partyMenu = nullptr;
	LazyNode<InventoryMenu>* inventoryMenu = nullptr;
	LazyNode<AlchemyMenu>* alchemyMenu = nullptr;
	LazyNode<BlacksmithingMenu>* blacksmithingMenu = nullptr;
	LazyNode<DismantleMenu>* dismantleMenu = nullptr;
	FadeHud* fadeHud = nullptr;
	LazyNode<PlatformerPauseMenu>* platformerPauseMenu = nullptr;
	MiniMap* miniMap = nullptr;

	std::string transition;
};
