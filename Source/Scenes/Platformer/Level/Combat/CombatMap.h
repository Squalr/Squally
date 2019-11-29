#pragma once

#include "Scenes/MapBase.h"

class CollectablesMenu;
class CombatHud;
class ChoicesMenu;
class DefeatMenu;
class EnemyAIHelper;
class InventoryMenu;
class MapMenu;
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

private:
	typedef MapBase super;
	void onEnter() override;
	void onExit() override;
	void initializePositions() override;
	void initializeListeners() override;
	void spawnEntities();

	CollectablesMenu* collectablesMenu;
	MapMenu* mapMenu;
	PartyMenu* partyMenu;
	InventoryMenu* inventoryMenu;

	TargetSelectionMenu* targetSelectionMenu;
	ChoicesMenu* choicesMenu;
	CombatHud* combatHud;
	TextOverlays* textOverlays;
	DefeatMenu* defeatMenu;
	RewardsMenu* rewardsMenu;
	Timeline* timeline;
	EnemyAIHelper* enemyAIHelper;
	NotificationHud* notificationHud;

	bool playerFirstStrike;
	std::vector<CombatData> playerData;
	std::vector<CombatData> enemyData;
	std::string enemyIdentifier;

	PlatformerEntityDeserializer* platformerEntityDeserializer;

	static const std::string MapPropertyPlayerFirstStrike;
	static const std::string MapPropertyEnemyFirstStrike;
};
