#pragma once
#include <string>
#include <functional>
#include <vector>

class Cutscene;
class HexusOpponentData;
class PlatformerEnemy;
class Squally;
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

	struct NavigateCipherArgs
	{
		bool todo;

		NavigateCipherArgs(bool todo) : todo(todo)
		{
		}
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
			BalmerPeaks,
			CastleValgrind,
			DaemonsHallow,
			EndianForest,
			LambdaCrypts,
			SeaSharpCaverns,
			UnderflowRuins,
			VoidStar,
			PuzzleTraining,
			PuzzleBalmerPeaks,
			PuzzleCastleValgrind,
			PuzzleDaemonsHallow,
			PuzzleEndianForest,
			PuzzleLambdaCrypts,
			PuzzleSeaSharpCaverns,
			PuzzleUnderflowRuins,
			PuzzleVoidStar,
		};

		Chapter chapter;

		NavigateHexusOpponentSelectArgs(Chapter chapter) : chapter(chapter) { }
	};

	struct NavigateCombatArgs
	{
		bool playerFirstStrike;
		std::string enemyIdentifier;
		std::string levelFile;
		std::vector<std::string> playerTypes;
		std::vector<std::string> enemyTypes;

		NavigateCombatArgs(bool playerFirstStrike, std::string enemyIdentifier, std::string levelFile, std::vector<std::string> playerTypes, std::vector<std::string> enemyTypes) : playerFirstStrike(playerFirstStrike), enemyIdentifier(enemyIdentifier), levelFile(levelFile), playerTypes(playerTypes), enemyTypes(enemyTypes) { }
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
	static void navigateCipherPuzzleSelect();
	static void navigateCipher(NavigateCipherArgs args);
	static void navigateHexus(NavigateHexusArgs args);
	static void navigateHexusRewards(NavigateHexusRewardArgs args);
	static void navigateHexusDeckManagement();
	static void navigateHexusShop();
	static void navigateHexusChapterSelect();
	static void navigateHexusOpponentSelect(NavigateHexusOpponentSelectArgs args);
	static void navigateHexusPuzzlesChapterSelect();
	static void navigateCombat(NavigateCombatArgs args);
	static void navigateCutscene(NavigateCutsceneArgs args);
	
	static const std::string EventNavigateTitle;
	static const std::string EventNavigateLoadingScreen;
	static const std::string EventNavigateMap;
	static const std::string EventNavigateSaveSelect;
	static const std::string EventNavigateMinigames;
	static const std::string EventNavigateOptions;
	static const std::string EventNavigateWorldMap;
	static const std::string EventNavigateCipher;
	static const std::string EventNavigateCipherPuzzleSelect;
	static const std::string EventNavigateHexus;
	static const std::string EventNavigateHexusRewards;
	static const std::string EventNavigateHexusDeckManagement;
	static const std::string EventNavigateHexusShop;
	static const std::string EventNavigateHexusChapterSelect;
	static const std::string EventNavigateHexusOpponentSelect;
	static const std::string EventNavigateHexusPuzzlesChapterSelect;
	static const std::string EventNavigateCombat;
	static const std::string EventNavigateCutscene;
};
