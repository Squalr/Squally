#pragma once

#include "Engine/Maps/GameObject.h"

class CombatSpawn : public GameObject
{
public:
	static CombatSpawn* create(cocos2d::ValueMap& initProperties);

	enum SpawnType
	{
		Player,
		Enemy
	};

	SpawnType getSpawnType();
	int getSpawnOrder();

	static const std::string MapKeyCombatSpawn;

private:
	typedef GameObject super;
	CombatSpawn(cocos2d::ValueMap& initProperties);
	virtual ~CombatSpawn();

	void onEnter() override;
	void initializeListeners() override;

	SpawnType spawnType;
	int spawnOrder;

	static const std::string MapKeySpawnType;
	static const std::string MapKeySpawnOrder;
	static const std::string MapKeyPlayerSpawn;
	static const std::string MapKeyEnemySpawn;
};
