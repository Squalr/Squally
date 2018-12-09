#include "SceneEvents.h"

#include "cocos2d.h"

using namespace cocos2d;

const std::string SceneEvents::BeforeSceneChangeEvent = "EVENT_BEFORE_SCENE_CHANGE";

void SceneEvents::TriggerBeforeSceneChange()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		SceneEvents::BeforeSceneChangeEvent
	);
}
