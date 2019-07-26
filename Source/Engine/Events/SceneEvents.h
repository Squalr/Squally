#pragma once
#include <string>

class SceneEvents
{
public:
	static void TriggerBeforeSceneChange();

	static const std::string EventBeforeSceneChange;
};
