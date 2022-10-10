#pragma once

#include "Scenes/MapBase.h"

class CardsMenu;
class CancelMenu;
class ChoicesMenu;
class CollectablesMenu;
class CombatAIHelper;
class CombatHud;
class ConfirmationHud;
class DefeatMenu;
class FocusTakeOver;
class FirstStrikeMenu;
class HackerModeWarningHud;
template <class T> class LazyNode;
class Lexicon;
class NotificationHud;
class PartyMenu;
class PlatformerEntityDeserializer;
class PlatformerPauseMenu;
class RewardsMenu;
class Scrappy;
class TargetSelectionMenu;
class Timeline;

class CombatMap : public MapBase
{
public:
	struct StatsOverrides
	{
		int health = 0;
		int mana = 0;
		bool useOverrides = false;

		StatsOverrides() { }
		StatsOverrides(int health, int mana) : health(health), mana(mana), useOverrides(true) { }
	};

	struct CombatData
	{
		std::string entityType;
		std::string identifier;
		std::string battleBehavior;
		std::string dropPool;
		StatsOverrides statsOverrides;

		CombatData(std::string entityType, std::string identifier, std::string battleBehavior, StatsOverrides statsOverrides = StatsOverrides(), std::string dropPool = "")
			: entityType(entityType), identifier(identifier), battleBehavior(battleBehavior), statsOverrides(statsOverrides), dropPool(dropPool) { }
	};

	static CombatMap* create(std::string levelFile, bool playerFirstStrike, std::vector<CombatData> playerData, std::vector<CombatData> enemyData);

protected:
	CombatMap(std::string levelFile, bool playerFirstStrike, std::vector<CombatData> playerData, std::vector<CombatData> enemyData);
	virtual ~CombatMap();

	void onEnter() override;
	void onExit() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onHackerModeEnable() override;
	void openPauseMenu(cocos2d::Node* refocusTarget) override;

private:
	typedef MapBase super;

	void spawnEntities();
	CollectablesMenu* buildCollectablesMenu();
	Lexicon* buildLexicon();
	CardsMenu* buildCardsMenu();
	PartyMenu* buildPartyMenu();
	PlatformerPauseMenu* buildPlatformerPauseMenu();

	LazyNode<CollectablesMenu>* collectablesMenu = nullptr;
	LazyNode<Lexicon>* lexiconMenu = nullptr;
	LazyNode<CardsMenu>* cardsMenu = nullptr;
	LazyNode<PartyMenu>* partyMenu = nullptr;
	LazyNode<PlatformerPauseMenu>* platformerPauseMenu = nullptr;

	TargetSelectionMenu* targetSelectionMenu = nullptr;
	ChoicesMenu* choicesMenu = nullptr;
	CancelMenu* cancelMenu = nullptr;
	CombatHud* combatHud = nullptr;
	FirstStrikeMenu* firstStrikeMenu = nullptr;
	DefeatMenu* defeatMenu = nullptr;
	RewardsMenu* rewardsMenu = nullptr;
	Timeline* timeline = nullptr;
	CombatAIHelper* enemyAIHelper = nullptr;
	HackerModeWarningHud* hackerModeWarningHud = nullptr;
	NotificationHud* notificationHud = nullptr;
	ConfirmationHud* confirmationHud = nullptr;

	Hud* combatEndBackdrop = nullptr;

	Scrappy* scrappy = nullptr;

	FocusTakeOver* entityFocusTakeOver = nullptr;
	FocusTakeOver* focusTakeOver = nullptr;

	bool playerFirstStrike = false;
	std::vector<CombatData> playerData;
	std::vector<CombatData> enemyData;

	PlatformerEntityDeserializer* platformerEntityDeserializer = nullptr;

	static const std::string PropertyPlayerFirstStrike;
	static const std::string PropertyEnemyFirstStrike;
};
