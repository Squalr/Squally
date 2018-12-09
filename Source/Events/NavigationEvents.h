#pragma once
#include "cocos2d.h"

#include "Engine/Cutscenes/Cutscene.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Maps/SerializableMap.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

// Forward declarations
class Squally;
class PlatformerEnemy;
class SerializableMap;

class NavigationEvents
{
public:
	struct NavigateLoadingScreenArgs
	{
		std::string levelFile;
		std::function<void(SerializableMap*)> onLoadCallback;

		NavigateLoadingScreenArgs(std::string levelFile, std::function<void(SerializableMap*)> onLoadCallback) : levelFile(levelFile), onLoadCallback(onLoadCallback) { }
	};

	struct NavigateHexusArgs
	{
		HexusOpponentData* opponentData;

		NavigateHexusArgs(HexusOpponentData* opponentData) : opponentData(opponentData)
		{
		}
	};

	struct NavigateHexusRewardArgs
	{
		int reward;
		bool isRewardReduced;

		NavigateHexusRewardArgs(int reward, bool isRewardReduced) : reward(reward), isRewardReduced(isRewardReduced)
		{
		}
	};

	struct NavigateMapArgs
	{
		SerializableMap* levelMap;

		NavigateMapArgs(SerializableMap* levelMap) : levelMap(levelMap) { }
	};

	struct NavigateHexusOpponentSelectArgs
	{
		enum class Chapter
		{
			Training,
			Jungle,
			Ruins,
			Forest,
			Caverns,
			Castle,
			IceCaps,
			Volcano,
			Void,
			Mech
		};

		Chapter chapter;

		NavigateHexusOpponentSelectArgs(Chapter chapter) : chapter(chapter) { }
	};

	struct NavigateCombatArgs
	{
		std::string levelFile;
		Squally* squally;
		PlatformerEnemy* enemy;

		NavigateCombatArgs(std::string levelFile, Squally* squally, PlatformerEnemy* enemy) : levelFile(levelFile), squally(squally), enemy(enemy) { }
	};

	struct NavigateCutsceneArgs
	{
		Cutscene* cutscene;

		NavigateCutsceneArgs(Cutscene* cutscene) : cutscene(cutscene) { }
	};

	static void navigateBack(int backCount = 1);
	static void navigateTitle();
	static void navigateLoadingScreen(NavigateLoadingScreenArgs args);
	static void navigateMap(NavigateMapArgs args);
	static void navigateSaveSelect();
	static void navigateMinigames();
	static void navigateOptions();
	static void navigateWorldMap();
	static void navigateHexus(NavigateHexusArgs args);
	static void navigateHexusPuzzles();
	static void navigateHexusRewards(NavigateHexusRewardArgs args);
	static void navigateHexusDeckManagement();
	static void navigateHexusShop();
	static void navigateHexusChapterSelect();
	static void navigateHexusOpponentSelect(NavigateHexusOpponentSelectArgs args);
	static void navigateCombat(NavigateCombatArgs args);
	static void navigateCutscene(NavigateCutsceneArgs args);
	
	static const std::string EventNavigateTitle;
	static const std::string EventNavigateLoadingScreen;
	static const std::string EventNavigateMap;
	static const std::string EventNavigateSaveSelect;
	static const std::string EventNavigateMinigames;
	static const std::string EventNavigateOptions;
	static const std::string EventNavigateWorldMap;
	static const std::string EventNavigateHexus;
	static const std::string EventNavigateHexusPuzzles;
	static const std::string EventNavigateHexusRewards;
	static const std::string EventNavigateHexusDeckManagement;
	static const std::string EventNavigateHexusShop;
	static const std::string EventNavigateHexusChapterSelect;
	static const std::string EventNavigateHexusOpponentSelect;
	static const std::string EventNavigateCombat;
	static const std::string EventNavigateCutscene;
};
