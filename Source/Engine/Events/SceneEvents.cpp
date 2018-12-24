#include "SceneEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string SceneEvents::BeforeSceneChangeEvent = "EVENT_BEFORE_SCENE_CHANGE";

void SceneEvents::TriggerBeforeSceneChange()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		SceneEvents::BeforeSceneChangeEvent
	);
}
