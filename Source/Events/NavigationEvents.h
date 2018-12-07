#pragma once
#include "cocos2d.h"

#include "Engine/Cutscenes/Cutscene.h"
#include "Engine/Maps/SerializableMap.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/Squally/Squally.h"

using namespace cocos2d;

// Forward declarations
class Squally;
class PlatformerEnemy;
class SerializableMap;

class NavigationEvents
{
public:
	static const std::string EventNavigateTitle;
	static const std::string EventNavigateWorldMap;

	struct NavigateBackEventArgs
	{
		int backCount;

		NavigateBackEventArgs(int backCount) : backCount(backCount) { };
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
		std::string levelFile;
		Squally* squally;
		PlatformerEnemy* enemy;

		NavigateFightArgs(std::string levelFile, Squally* squally, PlatformerEnemy* enemy) : levelFile(levelFile), squally(squally), enemy(enemy) { }
	};

	struct NavigateConfirmArgs
	{
		std::string message;
		std::function<void()> confirmCallback;
		std::function<void()> cancelCallback;

		NavigateConfirmArgs(std::string message, std::function<void()> confirmCallback, std::function<void()> cancelCallback) :
			message(message), confirmCallback(confirmCallback), cancelCallback(cancelCallback) { }
	};

	/*
	static void navigateBack(int count = 1);
	static void navigate(GameScreen gameScreen);
	static void navigateConfirm(std::string confirmMessage, std::function<void()> confirmCallback, std::function<void()> cancelCallback);
	static void loadCutscene(Cutscene* cutscene);
	static void loadMap(std::string levelFile);
	static void enterLevel(SerializableMap* levelMap);
	static void enterCombat(std::string levelFile, Squally* squally, PlatformerEnemy* enemy);
	*/
};
