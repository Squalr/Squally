#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class NavigationEvents
{
public:
	static const std::string gameNavigateNewEvent;
	static const std::string gameNavigateBackEvent;
	static const std::string gameNavigateConfirmEvent;
	static const std::string gameNavigateLoadLevelEvent;
	static const std::string gameNavigateEnterLevelEvent;
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
		Fight,
		Hexium,
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
		void* levelMap;

		NavigateEnterLevelArgs(void* levelMap) : levelMap(levelMap) { }
	};

	struct NavigateFightArgs
	{
		std::tuple<void*, void*> entities;

		NavigateFightArgs(std::tuple<void*, void*> entities) : entities(entities) { }
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
	static void loadFight(std::tuple<void*, void*> entities);
	static void enterLevel(void* levelMap);
};
