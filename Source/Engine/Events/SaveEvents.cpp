#include "SaveEvents.h"

#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string SaveEvents::EventSoftSaveGameState = "EVENT_SOFT_SAVE_GAME_STATE";

void SaveEvents::TriggerSoftSaveGameState()
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		SaveEvents::EventSoftSaveGameState
	);
}
