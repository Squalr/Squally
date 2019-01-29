#pragma once
#include <string>

class PlatformerEntity;
class TimelineEntry;

class CombatEvents
{
public:
	static const std::string EventSpawn;
	static const std::string EventRequestUserAction;
	static const std::string EventItemSelected;
	static const std::string EventAttackSelected;
	static const std::string EventDefendSelected;
	static const std::string EventClearSelection;
	static const std::string EventUserActionMade;

	struct SpawnArgs
	{
		PlatformerEntity* entity;
		bool isEnemySpawn;
		int spawnIndex;

		SpawnArgs(PlatformerEntity* entity, bool isEnemySpawn, int spawnIndex) : entity(entity), isEnemySpawn(isEnemySpawn), spawnIndex(spawnIndex)
		{
		}
	};

	struct RequestUserActionArgs
	{
		TimelineEntry* entry;
		PlatformerEntity* entity;

		RequestUserActionArgs(TimelineEntry* entry, PlatformerEntity* entity) : entry(entry), entity(entity)
		{
		}
	};

	static void TriggerSpawn(SpawnArgs args);
	static void TriggerRequestUserAction(RequestUserActionArgs args);
	static void TriggerItemSelected();
	static void TriggerAttackSelected();
	static void TriggerDefendSelected();
	static void TriggerClearSelection();
	static void TriggerUserActionMade();
};
