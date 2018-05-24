#pragma once
#include "MouseEvents.h"

const std::string MouseEvents::MouseMoveEvent = "mouse_move_event";
const std::string MouseEvents::MouseCanClickEvent = "mouse_can_click_event";

void MouseEvents::TriggerMouseMove(MouseEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		MouseEvents::MouseMoveEvent, 
		&args
	);
}

void MouseEvents::TriggerCanClickEvent(MouseCanClickEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		MouseEvents::MouseCanClickEvent,
		&args
	);
}
