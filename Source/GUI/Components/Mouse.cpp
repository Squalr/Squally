#include "Mouse.h"

Mouse* Mouse::create()
{
	Mouse* mouse = new Mouse();

	mouse->autorelease();

	return mouse;
}

Mouse::Mouse()
{
	this->mouseSpriteIdle = Sprite::create(Resources::Menus_MouseIdle);
	this->mouseSpriteIdle->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->mouseSpritePoint = Sprite::create(Resources::Menus_MousePoint);
	this->mouseSpritePoint->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->mouseSpritePoint->setVisible(false);

	this->addChild(this->mouseSpriteIdle);
	this->addChild(this->mouseSpritePoint);

	this->InitializeListeners();
}

Mouse::~Mouse()
{
}

void Mouse::SetCanClick(bool canClick)
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

void Mouse::InitializeListeners()
{
	EventListenerMouse* mouseListener = EventListenerMouse::create();

	mouseListener->onMouseMove = CC_CALLBACK_1(Mouse::OnMouseMove, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void Mouse::OnMouseMove(EventMouse* event)
{
	this->mouseSpriteIdle->setPosition(Vec2(event->getCursorX(), event->getCursorY()));
	this->mouseSpritePoint->setPosition(Vec2(event->getCursorX(), event->getCursorY()));
}
