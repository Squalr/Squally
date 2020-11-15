#pragma once
#include <functional>
#include <string>

class SmartScene;

class NavigationEvents
{
public:
	static const std::string EventNavigateScene;

	struct LoadSceneArgs
	{
		std::function<SmartScene*()> sceneCreator;

		LoadSceneArgs(std::function<SmartScene*()> sceneCreator) : sceneCreator(sceneCreator) { }
	};

	static void LoadScene(LoadSceneArgs args);
};
