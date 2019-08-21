#include "DialogueEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string DialogueEvents::EventDialogueOpen = "EVENT_DIALOGUE_OPEN";

void DialogueEvents::TriggerDialogueOpen(DialogueOpenArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		DialogueEvents::EventDialogueOpen,
		&args
	);
}
