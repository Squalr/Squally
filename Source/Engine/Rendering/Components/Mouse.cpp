#include "Mouse.h"

Vec2 Mouse::mousePosition = Vec2::ZERO;

Mouse* Mouse::create()
{
	Mouse* instance = new Mouse();
	
	instance->autorelease();

	return instance;
}

Mouse::Mouse()
{
	this->mouseSpriteIdle = Sprite::create(Resources::Menus_MouseIdle);
	this->mouseSpritePoint = Sprite::create(Resources::Menus_MousePoint);

	this->mouseSpriteIdle->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->mouseSpritePoint->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->mouseSpritePoint->setVisible(false);

	this->addChild(this->mouseSpriteIdle);
	this->addChild(this->mouseSpritePoint);
}

Mouse::~Mouse()
{
}

void Mouse::onEnter()
{
	Node::onEnter();

	this->initializeListeners();

	// Initialize positions to whatever the previous saved position was (allows for seamless cursor across scenes)
	this->mouseSpriteIdle->setPosition(Vec2(Mouse::mousePosition));
	this->mouseSpritePoint->setPosition(Vec2(Mouse::mousePosition));

	this->setCanClick(false);
}

void Mouse::onMouseCanClickEvent(EventCustom* eventCustom)
{
	MouseEvents::MouseCanClickEventArgs* args = (MouseEvents::MouseCanClickEventArgs*)(eventCustom->getUserData());
	
	this->setCanClick(args->canClick);
}

void Mouse::setCanClick(bool canClick)
{
	if (canClick)
	{
		this->mouseSpriteIdle->setVisible(false);
		this->mouseSpritePoint->setVisible(true);
	}
	else
	{
		this->mouseSpriteIdle->setVisible(true);
		this->mouseSpritePoint->setVisible(false);
	}
}

void Mouse::initializeListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);

	EventListenerMouse* mouseListener = EventListenerMouse::create();
	EventListenerCustom* mouseCanClickListener = EventListenerCustom::create(
		MouseEvents::MouseCanClickEvent,
		CC_CALLBACK_1(Mouse::onMouseCanClickEvent, this)
	);

	mouseListener->onMouseMove = CC_CALLBACK_1(Mouse::onMouseMove, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseCanClickListener, this);
}

void Mouse::onMouseMove(EventMouse* event)
{
	Mouse::mousePosition = Vec2(event->getCursorX(), event->getCursorY());

	this->mouseSpriteIdle->setPosition(Mouse::mousePosition);
	this->mouseSpritePoint->setPosition(Mouse::mousePosition);

	this->setCanClick(false);
	MouseEvents::TriggerMouseMove(MouseEvents::MouseEventArgs(Mouse::mousePosition.x, Mouse::mousePosition.y, event));
}
