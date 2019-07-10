#pragma once

#include "Scenes/MapBase.h"

class CombatHud;
class ChoicesMenu;
class DefeatMenu;
class EnemyAIHelper;
class PlatformerEntityDeserializer;
class RewardsMenu;
class TargetSelectionMenu;
class TextOverlays;
class Timeline;

class CombatMap : public MapBase
{
public:
	static CombatMap* create(std::string levelFile, std::vector<std::string> mapArgs, bool playerFirstStrike,
		std::string enemyIdentifier, std::vector<std::string> playerTypes, std::vector<std::string> enemyTypes);

	void loadMap(std::string mapResource, std::vector<std::string> args = { }) override;

protected:
	CombatMap(std::string levelFile, std::vector<std::string> mapArgs, bool playerFirstStrike,
		std::string enemyIdentifier, std::vector<std::string> playerTypes, std::vector<std::string> enemyTypes);
	~CombatMap();

private:
	typedef MapBase super;
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void setEntityKeys(std::vector<std::string> playerEntityKeys, std::vector<std::string> enemyEntityKeys);
	void spawnEntities();

	TargetSelectionMenu* targetSelectionMenu;
	ChoicesMenu* choicesMenu;
	CombatHud* combatHud;
	TextOverlays* textOverlays;
	DefeatMenu* defeatMenu;
	RewardsMenu* rewardsMenu;
	Timeline* timeline;
	EnemyAIHelper* enemyAIHelper;

	std::vector<std::string> playerEntityKeys;
	std::vector<std::string> enemyEntityKeys;
	std::string enemyIdentifier;

	PlatformerEntityDeserializer* platformerEntityDeserializer;

	static const std::string MapKeyPropertyDisableHackerMode;
};
