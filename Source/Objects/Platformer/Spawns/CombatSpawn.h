#pragma once

#include "Engine/Maps/GameObject.h"

class CombatSpawn : public GameObject
{
public:
	static CombatSpawn* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	CombatSpawn(cocos2d::ValueMap& properties);
	virtual ~CombatSpawn();

	void onEnter() override;
	void initializeListeners() override;

private:
	typedef GameObject super;

	std::string getEventString();
	int getSpawnOrder();

	bool isEnemySpawn;
	int spawnOrder;
	float spawnObjectHeight;
	float zoom;

	static const std::string MapKeySpawnType;
	static const std::string MapKeySpawnOrder;
	static const std::string MapKeyPlayerSpawn;
	static const std::string MapKeyEnemySpawn;
	static const std::string PropertyZoom;
};
