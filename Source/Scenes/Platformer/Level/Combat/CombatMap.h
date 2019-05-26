#pragma once

#include "Scenes/MapBase.h"

class CombatHud;
class ChoicesMenu;
class DefeatMenu;
class EnemyAIHelper;
class RewardsMenu;
class TargetSelectionMenu;
class TextOverlays;
class Timeline;

class CombatMap : public MapBase
{
public:
	static void registerGlobalScene();

protected:
	CombatMap();
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

	static CombatMap* instance;
};
