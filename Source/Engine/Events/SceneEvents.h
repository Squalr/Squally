#pragma once
#include <string>

class SceneEvents
{
public:
	static void TriggerBeforeSceneChange();
	static void TriggerAfterSceneChange();

	static const std::string EventBeforeSceneChange;
	static const std::string EventAfterSceneChange;
};
