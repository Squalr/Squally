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
class InventoryMenu;
class NotificationHud;
class PartyMenu;
class PlatformerEntityDeserializer;
class RewardsMenu;
class TargetSelectionMenu;
class TextOverlays;
class Timeline;

class CombatMap : public MapBase
{
public:
	struct CombatData
	{
		std::string entityType;
		std::string battleBehavior;
		std::string dropPool;

		CombatData(std::string entityType, std::string battleBehavior, std::string dropPool = "") : entityType(entityType), battleBehavior(battleBehavior), dropPool(dropPool) { }
	};

	static CombatMap* create(std::string levelFile, bool playerFirstStrike, std::string enemyIdentifier,
		std::vector<CombatData> playerData, std::vector<CombatData> enemyData);

protected:
	CombatMap(std::string levelFile, bool playerFirstStrike, std::string enemyIdentifier,
		std::vector<CombatData> playerData, std::vector<CombatData> enemyData);
	~CombatMap();

	void update(float dt) override;

private:
	typedef MapBase super;
	void onEnter() override;
	void onExit() override;
	void initializePositions() override;
	void initializeListeners() override;
	void spawnEntities();

	CollectablesMenu* collectablesMenu;
	CardsMenu* cardsMenu;
	PartyMenu* partyMenu;
	InventoryMenu* inventoryMenu;

	TargetSelectionMenu* targetSelectionMenu;
	ChoicesMenu* choicesMenu;
	CombatHud* combatHud;
	TextOverlays* textOverlays;
	FirstStrikeMenu* firstStrikeMenu;
	DefeatMenu* defeatMenu;
	RewardsMenu* rewardsMenu;
	Timeline* timeline;
	CombatAIHelper* enemyAIHelper;
	NotificationHud* notificationHud;

	FocusTakeOver* entityFocusTakeOver;
	FocusTakeOver* focusTakeOver;

	bool playerFirstStrike;
	std::vector<CombatData> playerData;
	std::vector<CombatData> enemyData;
	std::string enemyIdentifier;

	PlatformerEntityDeserializer* platformerEntityDeserializer;

	static const std::string MapPropertyPlayerFirstStrike;
	static const std::string MapPropertyEnemyFirstStrike;
};
