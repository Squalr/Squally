#include "InputEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string InputEvents::EventMouseMove = "EVENT_MOUSE_MOVE";
const std::string InputEvents::EventMouseRefresh = "EVENT_MOUSE_REFRESH";
const std::string InputEvents::EventMouseDown = "EVENT_MOUSE_DOWN";
const std::string InputEvents::EventMouseUp = "EVENT_MOUSE_UP";
const std::string InputEvents::EventMouseScroll = "EVENT_MOUSE_SCROLL";
const std::string InputEvents::EventClickableMouseOver = "EVENT_CLICKABLE_MOUSE_OVER";
const std::string InputEvents::EventClickableMouseOut = "EVENT_CLICKABLE_MOUSE_OUT";
const std::string InputEvents::EventMouseDrag = "EVENT_MOUSE_DRAG";
const std::string InputEvents::EventMouseStateUpdate = "EVENT_MOUSE_STATE_UPDATE";
const std::string InputEvents::EventKeyJustPressed = "EVENT_KEY_JUST_PRESSED";
const std::string InputEvents::EventKeyJustReleased = "EVENT_KEY_JUST_RELEASED";

void InputEvents::TriggerMouseMove(MouseEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		InputEvents::EventMouseMove,
		&args
	);
}

void InputEvents::TriggerMouseRefresh(MouseEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		InputEvents::EventMouseRefresh,
		&args
	);
}

void InputEvents::TriggerMouseDown(MouseEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		InputEvents::EventMouseDown,
		&args
	);
}

void InputEvents::TriggerMouseUp(MouseEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		InputEvents::EventMouseUp,
		&args
	);
}

void InputEvents::TriggerMouseScroll(MouseEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		InputEvents::EventMouseScroll,
		&args
	);
}

void InputEvents::TriggerStateChange(MouseEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		InputEvents::EventMouseStateUpdate,
		&args
	);
}

void InputEvents::TriggerEventClickableMouseOver()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		InputEvents::EventClickableMouseOver
	);
}

void InputEvents::TriggerEventClickableMouseOut()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		InputEvents::EventClickableMouseOut
	);
}

void InputEvents::TriggerDragEvent()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		InputEvents::EventMouseDrag
	);
}

void InputEvents::TriggerKeyJustPressed(KeyboardEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		InputEvents::EventKeyJustPressed,
		&args
	);
}

void InputEvents::TriggerKeyJustReleased(KeyboardEventArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		InputEvents::EventKeyJustReleased,
		&args
	);
}
