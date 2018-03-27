#pragma once
#include "cocos2d.h"
#include "Gui/Components/Mouse.h"
#include "Utils/StrUtils.h"

using namespace cocos2d;

class GameUtils
{
public:
	static const std::string gameNavigateNewEvent;
	static const std::string gameNavigateBackEvent;
	static const std::string gameNavigateConfirmEvent;
	static const std::string gameNavigateLoadLevelEvent;
	static const std::string gameNavigateEnterLevelEvent;

	enum GameScreen {
		Title,
		StoryMap,
		Tutorial,
		Pause,
		Options,
		Confirm,
		Loading,
		Level,
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
	static void enterLevel(void* levelMap);
	static void pause(Node *node);
	static void resume(Node *node);
	static void resumeAll();
	static bool isFocused(Node *node);
	static void focus(Node *node);
	static Node* changeParent(Node* node, Node* newParent, bool retainPosition);
	static void accelerateParticles(ParticleSystem* particleSystem, float duration);
	static void fadeInObject(Node* node, float delay, float duration);
	static Rect getSceneBounds(Node* node);
	static Rect getSceneBoundsV2(Node* node);
	static bool isVisible(Node* node);
	static bool intersects(Node* node, Vec2 mousePos);
	static bool intersectsV2(Node* node, Vec2 mousePos);
	static bool keyExists(ValueMap valueMap, std::string key);
	static bool isSupportedImagePath(std::string str);
};

