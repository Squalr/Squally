#include "MouseState.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"

using namespace cocos2d;

MouseState* MouseState::instance = nullptr;
Vec2 MouseState::mouseInitialPosition = Vec2::ZERO;
Vec2 MouseState::mousePosition = Vec2::ZERO;
Vec2 MouseState::scrollDelta = Vec2::ZERO;
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

InputEvents::MouseEventArgs MouseState::getMouseState()
{
	return InputEvents::MouseEventArgs(MouseState::mouseInitialPosition, MouseState::mousePosition, MouseState::scrollDelta, MouseState::isDragging, MouseState::canClick, MouseState::isLeftClicked);
}

Vec2 MouseState::getMousePosition()
{
	return MouseState::mousePosition;
}

void MouseState::initializeListeners()
{
	super::initializeListeners();

	/*
	EventListenerCustom* clickableMouseOverListener = EventListenerCustom::create(
		InputEvents::EventClickableMouseOver,
		CC_CALLBACK_1(MouseState::onEventClickableMouseOver, this)
	);

	EventListenerCustom* clickableMouseOutListener = EventListenerCustom::create(
		InputEvents::EventClickableMouseOut,
		CC_CALLBACK_1(MouseState::onEventClickableMouseOut, this)
	);

	EventListenerCustom* mouseDragListener = EventListenerCustom::create(
		InputEvents::EventMouseDrag,
		CC_CALLBACK_1(MouseState::onEventMouseDrag, this)
	);

	mouseListener->onMouseMove = CC_CALLBACK_1(MouseState::onMouseMove, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(MouseState::onMouseDown, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(MouseState::onMouseUp, this);
	mouseListener->onMouseScroll = CC_CALLBACK_1(MouseState::onMouseScroll, this);

	this->addGlobalEventListener(clickableMouseOverListener);
	this->addGlobalEventListener(clickableMouseOutListener);
	this->addGlobalEventListener(mouseDragListener);
	*/
}

void MouseState::onMouseDown(EventMouse* event)
{
}

void MouseState::onMouseUp(EventMouse* event)
{
}

void MouseState::onMouseMove(EventMouse* event)
{
}

void MouseState::onMouseScroll(cocos2d::EventMouse* event)
{
}

void MouseState::onEventClickableMouseOver(EventCustom* eventCustom)
{
	MouseState::canClick = true;

	InputEvents::TriggerStateChange(MouseState::getMouseState());
}

void MouseState::onEventClickableMouseOut(EventCustom* eventCustom)
{
	MouseState::canClick = false;

	InputEvents::TriggerStateChange(MouseState::getMouseState());
}

void MouseState::onEventMouseDrag(EventCustom* eventCustom)
{
	MouseState::isDragging = true;

	InputEvents::TriggerStateChange(MouseState::getMouseState());
}
