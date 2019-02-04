#pragma once

#include "Scenes/Maps/MapBase.h"

class CombatHud;
class ChoicesMenu;
class PlatformerEntity;
class TargetSelectionMenu;
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
	Timeline* timeline;
	std::vector<std::string> playerEntityKeys;
	std::vector<std::string> enemyEntityKeys;
	std::vector<PlatformerEntity*> playerEntities;
	std::vector<PlatformerEntity*> enemyEntities;

	static CombatMap* instance;
};
