#include "DialogEvents.h"

const std::string DialogEvents::DialogOpenEvent = "dialog_open_event";

void DialogEvents::TriggerDialog(DialogOpenArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		DialogEvents::DialogOpenEvent,
		&args
	);
}
