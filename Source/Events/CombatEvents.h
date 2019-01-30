#pragma once
#include <string>

class PlatformerEntity;
class TimelineEntry;

class CombatEvents
{
public:
	static const std::string EventSpawn;
	static const std::string EventChangeMenuState;
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

	struct MenuStateArgs
	{
		enum class CurrentMenu
		{
			ActionSelect,
			ItemSelect,
			AttackSelect,
			DefendSelect,
			ChooseAttackTarget,
			ChooseBuffTarget,
		};

		CurrentMenu currentMenu;
		TimelineEntry* entry;

		MenuStateArgs(CurrentMenu currentMenu, TimelineEntry* entry) : currentMenu(currentMenu), entry(entry)
		{
		}
	};

	static void TriggerSpawn(SpawnArgs args);
	static void TriggerMenuStateChange(MenuStateArgs args);
	static void TriggerUserActionMade();
};
