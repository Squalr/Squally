#pragma once
#include <string>

class PlatformerEntity;

class CombatEvents
{
public:
	static const std::string SpawnEvent;

	struct SpawnArgs
	{
		PlatformerEntity* entity;
		bool isEnemySpawn;
		int spawnIndex;

		SpawnArgs(PlatformerEntity* entity, bool isEnemySpawn, int spawnIndex) : entity(entity), isEnemySpawn(isEnemySpawn), spawnIndex(spawnIndex)
		{
		}
	};

	static void TriggerSpawn(SpawnArgs args);
};
