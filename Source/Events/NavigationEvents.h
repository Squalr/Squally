#pragma once
#include "cocos2d.h"

#include "Engine/Cutscenes/Cutscene.h"
#include "Engine/Maps/SerializableMap.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Resources.h"

using namespace cocos2d;

// Forward declarations
class Squally;
class PlatformerEnemy;
class SerializableMap;

class NavigationEvents
{
public:
	static const std::string gameNavigateNewEvent;
	static const std::string gameNavigateBackEvent;
	static const std::string gameNavigateConfirmEvent;
	static const std::string gameNavigateLoadCutsceneEvent;
	static const std::string gameNavigateLoadLevelEvent;
	static const std::string gameNavigateEnterLevelEvent;
	static const std::string gameNavigateFightEvent;

	enum GameScreen {
		Title,
		StoryMap,
		SaveSelect,
		Minigames,
		Minigames_Hexus,
		Minigames_Hexus_Chapter_Training,
		Minigames_Hexus_Chapter_Jungle,
		Minigames_Hexus_Chapter_Ruins,
		Minigames_Hexus_Chapter_Forest,
		Minigames_Hexus_Chapter_Caverns,
		Minigames_Hexus_Chapter_Castle,
		Minigames_Hexus_Chapter_IceCaps,
		Minigames_Hexus_Chapter_Volcano,
		Minigames_Hexus_Chapter_Obelisk,
		Minigames_Hexus_Chapter_Mech,
		Minigames_Hexus_Puzzles,
		Tutorial,
		Pause,
		Options,
		Confirm,
		Loading,
		Level,
		LevelEditor,
		Fight,
		Hexus,
		Cutscene_IntroSequence,
	};

	struct NavigateBackEventArgs
	{
		int backCount;

		NavigateBackEventArgs(int backCount) : backCount(backCount) { };
	};

	struct NavigateEventArgs
	{
		GameScreen gameScreen;

		NavigateEventArgs(GameScreen gameScreen) : gameScreen(gameScreen) { }
	};

	struct NavigateLoadCutsceneArgs
	{
		Cutscene* cutscene;

		NavigateLoadCutsceneArgs(Cutscene* cutscene) : cutscene(cutscene) { }
	};

	struct NavigateLoadLevelArgs
	{
		std::string levelFile;

		NavigateLoadLevelArgs(std::string levelFile) : levelFile(levelFile) { }
	};

	struct NavigateEnterLevelArgs
	{
		SerializableMap* levelMap;

		NavigateEnterLevelArgs(SerializableMap* levelMap) : levelMap(levelMap) { }
	};

	struct NavigateFightArgs
	{
		Squally* squally;
		PlatformerEnemy* enemy;

		NavigateFightArgs(Squally* squally, PlatformerEnemy* enemy) : squally(squally), enemy(enemy) { }
	};

	struct NavigateConfirmArgs
	{
		std::string message;
		std::function<void()> confirmCallback;
		std::function<void()> cancelCallback;

		NavigateConfirmArgs(std::string message, std::function<void()> confirmCallback, std::function<void()> cancelCallback) :
			message(message), confirmCallback(confirmCallback), cancelCallback(cancelCallback) { }
	};

	static void navigateBack(int count = 1);
	static void navigate(GameScreen gameScreen);
	static void navigateConfirm(std::string confirmMessage, std::function<void()> confirmCallback, std::function<void()> cancelCallback);
	static void loadCutscene(Cutscene* cutscene);
	static void loadMap(std::string levelFile);
	static void enterLevel(SerializableMap* levelMap);
	static void loadFight(Squally* squally, PlatformerEnemy* enemy);
};
