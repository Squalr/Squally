#pragma once

#include "Scenes/MapBase.h"

class CardsMenu;
class ChoicesMenu;
class CollectablesMenu;
class CombatAIHelper;
class CombatHud;
class DefeatMenu;
class FocusTakeOver;
class FirstStrikeMenu;
class HackerModeWarningHud;
class InventoryMenu;
class NotificationHud;
class PartyMenu;
class PlatformerEntityDeserializer;
class RewardsMenu;
class Scrappy;
class TargetSelectionMenu;
class TextOverlays;
class Timeline;

class CombatMap : public MapBase
{
public:
	struct StatsOverrides
	{
		int health;
		int mana;
		bool useOverrides;

		StatsOverrides() : health(0), mana(0), useOverrides(false) { }
		StatsOverrides(int health, int mana) : health(health), mana(mana), useOverrides(true) { }
	};

	struct CombatData
	{
		std::string entityType;
		std::string battleBehavior;
		std::string dropPool;
		StatsOverrides statsOverrides;

		CombatData(std::string entityType, std::string battleBehavior, StatsOverrides statsOverrides = StatsOverrides(), std::string dropPool = "")
			: entityType(entityType), battleBehavior(battleBehavior), statsOverrides(statsOverrides), dropPool(dropPool) { }
	};

	static CombatMap* create(std::string levelFile, bool playerFirstStrike, std::string enemyIdentifier,
		std::vector<CombatData> playerData, std::vector<CombatData> enemyData);

protected:
	CombatMap(std::string levelFile, bool playerFirstStrike, std::string enemyIdentifier,
		std::vector<CombatData> playerData, std::vector<CombatData> enemyData);
	virtual ~CombatMap();

	void onEnter() override;
	void onExit() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef MapBase super;

	void spawnEntities();

	CollectablesMenu* collectablesMenu;
	CardsMenu* cardsMenu;
	PartyMenu* partyMenu;
	InventoryMenu* inventoryMenu;

	TargetSelectionMenu* targetSelectionMenu;
	ChoicesMenu* choicesMenu;
	CombatHud* combatHud;
	FirstStrikeMenu* firstStrikeMenu;
	DefeatMenu* defeatMenu;
	RewardsMenu* rewardsMenu;
	Timeline* timeline;
	CombatAIHelper* enemyAIHelper;
	HackerModeWarningHud* hackerModeWarningHud;
	NotificationHud* notificationHud;

	Hud* combatEndBackdrop;

	Scrappy* scrappy;

	FocusTakeOver* entityFocusTakeOver;
	FocusTakeOver* focusTakeOver;

	bool playerFirstStrike;
	std::vector<CombatData> playerData;
	std::vector<CombatData> enemyData;
	std::string enemyIdentifier;

	PlatformerEntityDeserializer* platformerEntityDeserializer;

	static const std::string PropertyPlayerFirstStrike;
	static const std::string PropertyEnemyFirstStrike;
};
