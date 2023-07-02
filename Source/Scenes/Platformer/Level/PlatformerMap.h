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
class CutscenesMenu;
class DismantleMenu;
class GameHud;
class FadeHud;
class HelpMenu;
class Hexus;
class InventoryMenu;
class ItemInfoMenu;
template <class T> class LazyNode;
class Lexicon;
class NotificationHud;
class PlatformerPauseMenu;
class PartyMenu;
class QuickSwapMenu;
class MiniMap;

class PlatformerMap : public MapBase
{
public:
	static PlatformerMap* create(std::string transition = "");
	
	std::string& getTransition();
	
	static const std::string TransitionRespawn;

protected:
	PlatformerMap(std::string transition = "");
	virtual ~PlatformerMap();
	
	void initializePositions() override;
	void initializeListeners() override;
	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void onExit() override;
	bool loadMapFromTmx(std::string mapResource, cocos2d::cocos_experimental::TMXTiledMap* mapRaw, bool useFallback = true) override;
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
	Lexicon* buildLexicon();
	ItemInfoMenu* buildItemInfoMenu();
	CardsMenu* buildCardsMenu();
	PartyMenu* buildPartyMenu();
	QuickSwapMenu* buildQuickSwapMenu();
	InventoryMenu* buildInventoryMenu();
	AlchemyMenu* buildAlchemyMenu();
	BlacksmithingMenu* buildBlacksmithingMenu();
	DismantleMenu* buildDismantleMenu();
	PlatformerPauseMenu* buildPlatformerPauseMenu();
	CutscenesMenu* buildCutscenesMenu();

	bool awaitingConfirmationEnd = false;

	GameHud* gameHud = nullptr;
	ConfirmationHud* confirmationHud = nullptr;
	NotificationHud* notificationHud = nullptr;
	LazyNode<Cipher>* cipher = nullptr;
	LazyNode<Hexus>* hexus = nullptr;
	LazyNode<HelpMenu>* cardHelpMenu = nullptr;
	LazyNode<CollectablesMenu>* collectablesMenu = nullptr;
	LazyNode<Lexicon>* lexiconMenu = nullptr;
	LazyNode<ItemInfoMenu>* itemInfoMenu = nullptr;
	LazyNode<CardsMenu>* cardsMenu = nullptr;
	LazyNode<PartyMenu>* partyMenu = nullptr;
	LazyNode<QuickSwapMenu>* quickSwapMenu = nullptr;
	LazyNode<InventoryMenu>* inventoryMenu = nullptr;
	LazyNode<AlchemyMenu>* alchemyMenu = nullptr;
	LazyNode<BlacksmithingMenu>* blacksmithingMenu = nullptr;
	LazyNode<DismantleMenu>* dismantleMenu = nullptr;
	LazyNode<CutscenesMenu>* cutscenesMenu = nullptr;
	FadeHud* fadeHud = nullptr;
	LazyNode<PlatformerPauseMenu>* platformerPauseMenu = nullptr;
	MiniMap* miniMap = nullptr;

	bool autoClosePauseMenu = false;

	std::string transition;
};
