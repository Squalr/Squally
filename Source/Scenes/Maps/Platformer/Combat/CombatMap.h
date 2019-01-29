#pragma once

#include "Scenes/Maps/MapBase.h"

class ChoicesMenu;
class PlatformerEntity;
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
	void onUserAction();
	void setEntityKeys(std::vector<std::string> playerEntityKeys, std::vector<std::string> enemyEntityKeys);

	Timeline* timeline;
	ChoicesMenu* choicesMenu;
	std::vector<std::string> playerEntityKeys;
	std::vector<std::string> enemyEntityKeys;
	std::vector<PlatformerEntity*> playerEntities;
	std::vector<PlatformerEntity*> enemyEntities;

	static CombatMap* instance;
};
