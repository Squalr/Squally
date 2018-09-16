#include "MouseState.h"

MouseState* MouseState::instance = nullptr;
Vec2 MouseState::mousePosition = Vec2::ZERO;
bool MouseState::canClick = false;
bool MouseState::isDragging = false;
EventMouse::MouseButton MouseState::mouseButton = (EventMouse::MouseButton)0;

void MouseState::registerGlobalNode()
{
	if (MouseState::instance == nullptr)
	{
		MouseState::instance = new MouseState();

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

Vec2 MouseState::getMousePosition()
{
	return MouseState::mousePosition;
}

void MouseState::initializeListeners()
{
	GlobalNode::initializeListeners();

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

	mouseListener->onMouseMove = CC_CALLBACK_1(MouseState::onMouseMove, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(MouseState::onMouseDown, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(MouseState::onMouseUp, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(clickableMouseOverListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(clickableMouseOutListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseDragListener, this);
}

void MouseState::onMouseDown(EventMouse* event)
{
	MouseState::mousePosition = Vec2(event->getCursorX(), event->getCursorY());
	MouseState::mouseButton = event->getMouseButton();

	MouseEvents::TriggerMouseDown(this->buildArgs());
	MouseEvents::TriggerStateChange(this->buildArgs());
}

void MouseState::onMouseUp(EventMouse* event)
{
	MouseState::mousePosition = Vec2(event->getCursorX(), event->getCursorY());
	MouseState::mouseButton = event->getMouseButton();

	MouseEvents::TriggerMouseUp(this->buildArgs());
	MouseEvents::TriggerStateChange(this->buildArgs());
}

void MouseState::onMouseMove(EventMouse* event)
{
	MouseState::mousePosition = Vec2(event->getCursorX(), event->getCursorY());
	MouseState::mouseButton = event->getMouseButton();
	MouseState::canClick = false;

	MouseEvents::TriggerMouseMove(this->buildArgs());
	MouseEvents::TriggerStateChange(this->buildArgs());
}

void MouseState::onClickableMouseOverEvent(EventCustom* eventCustom)
{
	MouseState::canClick = true;

	MouseEvents::TriggerStateChange(this->buildArgs());
}

void MouseState::onClickableMouseOutEvent(EventCustom* eventCustom)
{
	MouseState::canClick = false;

	MouseEvents::TriggerStateChange(this->buildArgs());
}

void MouseState::onMouseDragEvent(EventCustom* eventCustom)
{
	MouseState::isDragging = true;

	MouseEvents::TriggerStateChange(this->buildArgs());
}

MouseEvents::MouseEventArgs MouseState::buildArgs()
{
	return MouseEvents::MouseEventArgs(MouseState::mousePosition, MouseState::isDragging, MouseState::canClick, MouseState::mouseButton);
}