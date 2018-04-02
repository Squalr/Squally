#pragma once
#include "MouseEvents.h"

const std::string MouseEvents::MouseMoveEvent = "mouse_move_event";

void MouseEvents::TriggerMouseMove(MouseEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		MouseEvents::MouseMoveEvent, 
		&args
	);
}
