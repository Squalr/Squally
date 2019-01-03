#include "MouseState.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventMouse.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventListenerMouse.h"

#include "Engine/GlobalDirector.h"

using namespace cocos2d;

MouseState* MouseState::instance = nullptr;
Vec2 MouseState::mousePosition = Vec2::ZERO;
bool MouseState::canClick = false;
bool MouseState::isDragging = false;
bool MouseState::isLeftClicked = false;

void MouseState::registerGlobalNode()
{
	if (MouseState::instance == nullptr)
	{
		MouseState::instance = new MouseState();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(MouseState::instance);
	}
}

MouseState::MouseState()
{
}

MouseState::~MouseState()
{
}

MouseEvents::MouseEventArgs MouseState::getMouseState()
{
	return MouseEvents::MouseEventArgs(MouseState::mousePosition, MouseState::isDragging, MouseState::canClick, MouseState::isLeftClicked);
}

Vec2 MouseState::getMousePosition()
{
	return MouseState::mousePosition;
}

void MouseState::initializeListeners()
{
	super::initializeListeners();

	EventListenerMouse* mouseListener = EventListenerMouse::create();

	EventListenerCustom* clickableMouseOverListener = EventListenerCustom::create(
		MouseEvents::ClickableMouseOverEvent,
		CC_CALLBACK_1(MouseState::onClickableMouseOverEvent, this)
	);

	EventListenerCustom* clickableMouseOutListener = EventListenerCustom::create(
		MouseEvents::ClickableMouseOutEvent,
		CC_CALLBACK_1(MouseState::onClickableMouseOutEvent, this)
	);

	EventListenerCustom* mouseDragListener = EventListenerCustom::create(
		MouseEvents::MouseDragEvent,
		CC_CALLBACK_1(MouseState::onMouseDragEvent, this)
	);

	EventListenerCustom* mouseScrollListener = EventListenerCustom::create(
		MouseEvents::MouseScrollEvent,
		CC_CALLBACK_0(MouseState::onMouseScroll, this)
	);

	mouseListener->onMouseMove = CC_CALLBACK_1(MouseState::onMouseMove, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(MouseState::onMouseDown, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(MouseState::onMouseUp, this);

	this->addGlobalEventListener(mouseListener);
	this->addGlobalEventListener(clickableMouseOverListener);
	this->addGlobalEventListener(clickableMouseOutListener);
	this->addGlobalEventListener(mouseDragListener);
	this->addGlobalEventListener(mouseScrollListener);
}

void MouseState::onMouseDown(EventMouse* event)
{
	MouseState::mousePosition = Vec2(event->getCursorX(), event->getCursorY());
	MouseState::isLeftClicked = (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT);

	MouseEvents::TriggerMouseDown(MouseState::getMouseState());
	MouseEvents::TriggerStateChange(MouseState::getMouseState());
}

void MouseState::onMouseUp(EventMouse* event)
{
	MouseState::mousePosition = Vec2(event->getCursorX(), event->getCursorY());
	MouseState::isLeftClicked = (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT);

	MouseEvents::TriggerMouseUp(MouseState::getMouseState());

	MouseState::isDragging = false;
	MouseState::canClick = false;

	MouseEvents::TriggerStateChange(MouseState::getMouseState());
	MouseEvents::TriggerMouseRefresh(MouseState::getMouseState());
}

void MouseState::onMouseMove(EventMouse* event)
{
	MouseState::mousePosition = Vec2(event->getCursorX(), event->getCursorY());
	MouseState::isLeftClicked = (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT);
	MouseState::canClick = false;

	MouseEvents::TriggerMouseMove(MouseState::getMouseState());
	MouseEvents::TriggerStateChange(MouseState::getMouseState());
}

void MouseState::onMouseScroll()
{
	MouseEvents::TriggerMouseRefresh(MouseState::getMouseState());
}

void MouseState::onClickableMouseOverEvent(EventCustom* eventCustom)
{
	MouseState::canClick = true;

	MouseEvents::TriggerStateChange(MouseState::getMouseState());
}

void MouseState::onClickableMouseOutEvent(EventCustom* eventCustom)
{
	MouseState::canClick = false;

	MouseEvents::TriggerStateChange(MouseState::getMouseState());
}

void MouseState::onMouseDragEvent(EventCustom* eventCustom)
{
	MouseState::isDragging = true;

	MouseEvents::TriggerStateChange(MouseState::getMouseState());
}
