#include "DialogEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string DialogEvents::EventDialogOpen = "EVENT_DIALOG_OPEN";

void DialogEvents::TriggerDialog(DialogOpenArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		DialogEvents::EventDialogOpen,
		&args
	);
}
