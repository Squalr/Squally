#include "SceneEvents.h"

const std::string SceneEvents::BeforeSceneChangeEvent = "EVENT_BEFORE_SCENE_CHANGE";

void SceneEvents::TriggerBeforeSceneChange()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		SceneEvents::BeforeSceneChangeEvent
	);
}
