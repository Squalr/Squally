#include "Mouse.h"
#include "Resources.h"

Mouse::Mouse()
{
	this->mouseSpriteIdle = Sprite::create(Resources::GUI_MouseIdle);
	this->mouseSpriteIdle->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->mouseSpritePoint = Sprite::create(Resources::GUI_MousePoint);
	this->mouseSpritePoint->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->mouseSpritePoint->setVisible(false);

	this->addChild(this->mouseSpriteIdle);
	this->addChild(this->mouseSpritePoint);
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

void Mouse::onEnter()
{
	Node::onEnter();

	this->InitializeListeners();
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
