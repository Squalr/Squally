#pragma once
#include <functional>
#include <string>

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

class SmartScene;

class NavigationEvents
{
public:
	static const std::string EventNavigateScene;

	struct LoadSceneArgs
	{
		SmartScene* scene;

		LoadSceneArgs(SmartScene* scene) : scene(scene) { }
	};

	static void LoadScene(LoadSceneArgs args);
	static void NavigateBack(int backCount = 1);
};
