#include "SaveEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string SaveEvents::EventSoftSaveGameState = "EVENT_SOFT_SAVE_GAME_STATE";

void SaveEvents::TriggerSoftSaveGameState()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		SaveEvents::EventSoftSaveGameState
	);
}
