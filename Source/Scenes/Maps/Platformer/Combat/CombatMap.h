#pragma once

#include "Scenes/Maps/MapBase.h"

class CombatHud;
class ChoicesMenu;
class EnemyAIHelper;
class PlatformerEntity;
class RewardsMenu;
class TargetSelectionMenu;
class TextOverlays;
class Timeline;

class CombatMap : public MapBase
{
public:
	static void registerGlobalScene();

	void loadMap(SerializableMap* levelMap) override;

	void initializeEntities();

protected:
	CombatMap();
	~CombatMap();

private:
	typedef MapBase super;
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;
	void setEntityKeys(std::vector<std::string> playerEntityKeys, std::vector<std::string> enemyEntityKeys);

	TargetSelectionMenu* targetSelectionMenu;
	ChoicesMenu* choicesMenu;
	CombatHud* combatHud;
	TextOverlays* textOverlays;
	RewardsMenu* rewardsMenu;
	Timeline* timeline;
	EnemyAIHelper* enemyAIHelper;

	std::vector<std::string> playerEntityKeys;
	std::vector<std::string> enemyEntityKeys;
	std::vector<PlatformerEntity*> playerEntities;
	std::vector<PlatformerEntity*> enemyEntities;
	std::string enemyIdentifier;

	static CombatMap* instance;
};
