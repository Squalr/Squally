#pragma once

#include "Scenes/Maps/MapBase.h"

class Timeline;

class CombatMap : public MapBase
{
public:
	static void registerGlobalScene();

	void loadMap(SerializableMap* levelMap) override;

	void setEntityKeys(std::vector<std::string> playerEntityKeys, std::vector<std::string> enemyEntityKeys);

protected:
	CombatMap();
	~CombatMap();

private:
	typedef MapBase super;
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

	void loadEntitiesFromKeys();

	Timeline* timeline;
	std::vector<std::string> playerEntityKeys;
	std::vector<std::string> enemyEntityKeys;

	static CombatMap* instance;
};
