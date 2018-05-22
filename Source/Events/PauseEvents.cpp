#pragma once
#include "PauseEvents.h"

const std::string PauseEvents::PauseEvent = "pause_event";

void PauseEvents::pauseLevel(PauseEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		PauseEvents::PauseEvent,
		&args
	);
}
