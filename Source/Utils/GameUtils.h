#pragma once
#include "cocos2d.h"
#include "Gui/Components/Mouse.h"

using namespace cocos2d;

class GameUtils
{
public:
	static const std::string gameNavigateNewEvent;
	static const std::string gameNavigateBackEvent;
	static const std::string gameNavigateNewLevelEvent;

	enum GameScreen {
		Title,
		StoryMap,
		Tutorial,
		Pause,
		Options,
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

	struct NavigateNewLevelEvent
	{
		std::string levelFile;

		NavigateNewLevelEvent(std::string levelFile = "") : levelFile(levelFile) { }
	};

	static void navigateBack(int count = 1);
	static void navigate(GameScreen gameScreen);
	static void loadLevel(std::string levelFile);
	static void pause(Node *node);
	static void resume(Node *node);
	static void resumeAll();
	static bool isFocused(Node *node);
	static void focus(Node *node);
	static void accelerateParticles(ParticleSystem* particleSystem, float duration);
	static void fadeInObject(Node* node, float delay, float duration);
	static Rect getSceneBounds(Node* node);
	static Rect getSceneBoundsV2(Node* node);
	static bool isVisible(Node* node);
	static bool intersects(Node* node, Vec2 mousePos);
	static bool intersectsV2(Node* node, Vec2 mousePos);
	static bool keyExists(ValueMap valueMap, std::string key);
};

