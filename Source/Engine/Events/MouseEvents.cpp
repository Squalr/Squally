#include "MouseEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string MouseEvents::EventMouseMove = "EVENT_MOUSE_MOVE";
const std::string MouseEvents::EventMouseRefresh = "EVENT_MOUSE_REFRESH";
const std::string MouseEvents::EventMouseDown = "EVENT_MOUSE_DOWN";
const std::string MouseEvents::EventMouseUp = "EVENT_MOUSE_UP";
const std::string MouseEvents::EventMouseScroll = "EVENT_MOUSE_SCROLL";
const std::string MouseEvents::EventClickableMouseOver = "EVENT_CLICKABLE_MOUSE_OVER";
const std::string MouseEvents::ClickableMouseOutEvent = "EVENT_CLICKABLE_MOUSE_OUT";
const std::string MouseEvents::EventMouseDrag = "EVENT_MOUSE_DRAG";
const std::string MouseEvents::EventMouseStateUpdate = "EVENT_MOUSE_STATE_UPDATE";

void MouseEvents::TriggerMouseMove(MouseEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		MouseEvents::EventMouseMove,
		&args
	);
}

void MouseEvents::TriggerMouseRefresh(MouseEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		MouseEvents::EventMouseRefresh,
		&args
	);
}

void MouseEvents::TriggerMouseDown(MouseEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		MouseEvents::EventMouseDown,
		&args
	);
}

void MouseEvents::TriggerMouseUp(MouseEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		MouseEvents::EventMouseUp,
		&args
	);
}

void MouseEvents::TriggerMouseScroll(MouseEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		MouseEvents::EventMouseScroll,
		&args
	);
}

void MouseEvents::TriggerStateChange(MouseEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		MouseEvents::EventMouseStateUpdate,
		&args
	);
}

void MouseEvents::TriggerEventClickableMouseOver()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		MouseEvents::EventClickableMouseOver
	);
}

void MouseEvents::TriggerClickableMouseOutEvent()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		MouseEvents::ClickableMouseOutEvent
	);
}

void MouseEvents::TriggerDragEvent()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		MouseEvents::EventMouseDrag
	);
}
