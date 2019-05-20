#pragma once
#include <string>
#include <functional>
#include <map>
#include <vector>

#include "cocos/base/CCValue.h"

class Cutscene;
class CipherPuzzleData;
class HexusOpponentData;
class PlatformerEnemy;
class Squally;
class SerializableMap;

class NavigationEvents
{
public:
	struct NavigateCipherPuzzleSelectArgs
	{
		enum class Chapter
		{
			BalmerPeaks,
			CastleValgrind,
			DaemonsHallow,
			EndianForest,
			LambdaCrypts,
			SeaSharpCaverns,
			UnderflowRuins,
			VoidStar,
		};

		NavigateCipherPuzzleSelectArgs::Chapter chapter;

		NavigateCipherPuzzleSelectArgs(NavigateCipherPuzzleSelectArgs::Chapter chapter) : chapter(chapter) { }
	};

	struct NavigateCipherArgs
	{
		CipherPuzzleData* cipherPuzzleData;

		NavigateCipherArgs(CipherPuzzleData* cipherPuzzleData) : cipherPuzzleData(cipherPuzzleData)
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
		bool isChapterClear;

		NavigateHexusRewardArgs(int reward, bool isRewardReduced = false, bool isChapterClear = false) : reward(reward), isRewardReduced(isRewardReduced), isChapterClear(isChapterClear)
		{
		}
	};

	struct NavigateMapArgs
	{
		std::string mapResource;
		std::string mapArgs;

		NavigateMapArgs(std::string mapResource, std::string mapArgs) : mapResource(mapResource), mapArgs(mapArgs) { }
	};

	struct NavigatePointerTraceMapArgs
	{
		std::string mapResource;
		std::function<void()> onLevelClearCallback;

		NavigatePointerTraceMapArgs(std::string mapResource, std::function<void()> onLevelClearCallback) : mapResource(mapResource), onLevelClearCallback(onLevelClearCallback) { }
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

		NavigateHexusOpponentSelectArgs::Chapter chapter;

		NavigateHexusOpponentSelectArgs(NavigateHexusOpponentSelectArgs::Chapter chapter) : chapter(chapter) { }
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
	static void navigatePlatformerMap(NavigateMapArgs args);
	static void navigateCombatMap(NavigateMapArgs args);
	static void navigatePointerTraceMap(NavigatePointerTraceMapArgs args);
	static void navigateSaveSelect();
	static void navigateMinigames();
	static void navigateOptions();
	static void navigateWorldMap();
	static void navigatePointerTrace();
	static void navigatePointerTraceLevelSelect();
	static void navigateCipherChapterSelect();
	static void navigateCipherPuzzleSelect(NavigateCipherPuzzleSelectArgs args);
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
	static const std::string EventNavigatePlatformerMap;
	static const std::string EventNavigateCombatMap;
	static const std::string EventNavigatePointerTraceMap;
	static const std::string EventNavigateSaveSelect;
	static const std::string EventNavigateMinigames;
	static const std::string EventNavigateOptions;
	static const std::string EventNavigateWorldMap;
	static const std::string EventNavigatePointerTrace;
	static const std::string EventNavigatePointerTraceLevelSelect;
	static const std::string EventNavigateCipher;
	static const std::string EventNavigateCipherChapterSelect;
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
