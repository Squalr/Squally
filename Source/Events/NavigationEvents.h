#pragma once
#include "cocos2d.h"

#include "Entities/Player/Player.h"
#include "Entities/Enemy.h"
#include "Resources.h"
#include "Scenes/Level/LevelMap.h"

using namespace cocos2d;

// Forward declarations
class Player;
class Enemy;
class LevelMap;

class NavigationEvents
{
public:
	static const std::string gameNavigateNewEvent;
	static const std::string gameNavigateBackEvent;
	static const std::string gameNavigateConfirmEvent;
	static const std::string gameNavigateLoadLevelEvent;
	static const std::string gameNavigateEnterLevelEvent;
	static const std::string gameNavigateLoadLevelEditorEvent;
	static const std::string gameNavigateEnterLevelEditorEvent;
	static const std::string gameNavigateFightEvent;

	enum GameScreen {
		Title,
		StoryMap,
		Tutorial,
		Pause,
		Options,
		Confirm,
		Loading,
		Level,
		LevelEditor,
		Fight,
		Hexus,
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

	struct NavigateLoadLevelArgs
	{
		std::string levelFile;

		NavigateLoadLevelArgs(std::string levelFile) : levelFile(levelFile) { }
	};

	struct NavigateEnterLevelArgs
	{
		LevelMap* levelMap;

		NavigateEnterLevelArgs(LevelMap* levelMap) : levelMap(levelMap) { }
	};

	struct NavigateLoadLevelEditorArgs
	{
		std::string levelFile;
		Vec2 initPosition;

		NavigateLoadLevelEditorArgs(std::string levelFile, Vec2 initPosition) : levelFile(levelFile), initPosition(initPosition) { }
	};

	struct NavigateEnterLevelEditorArgs
	{
		LevelMap* levelMap;
		Vec2 initPosition;

		NavigateEnterLevelEditorArgs(LevelMap* levelMap, Vec2 initPosition) : levelMap(levelMap), initPosition(initPosition) { }
	};

	struct NavigateFightArgs
	{
		Player* player;
		Enemy* enemy;

		NavigateFightArgs(Player*player, Enemy* enemy) : player(player), enemy(enemy) { }
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
	static void loadLevel(std::string levelFile);
	static void enterLevel(LevelMap* levelMap);
	static void loadLevelEditor(std::string levelFile, Vec2 initPosition);
	static void enterLevelEditor(LevelMap* levelMap, Vec2 initPosition);
	static void loadFight(Player* player, Enemy* enemy);
};
