#include "SceneEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string SceneEvents::EventBeforeSceneChange = "EVENT_BEFORE_SCENE_CHANGE";
const std::string SceneEvents::EventAfterSceneChange = "EVENT_AFTER_SCENE_CHANGE";

void SceneEvents::TriggerBeforeSceneChange()
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		SceneEvents::EventBeforeSceneChange
	);
}

void SceneEvents::TriggerAfterSceneChange()
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		SceneEvents::EventAfterSceneChange
	);
}
