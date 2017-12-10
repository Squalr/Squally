#include "Mouse.h"
#include "Resources.h"

Mouse::Mouse()
{
	this->mouseSpriteIdle = Sprite::create(Resources::GUI_MouseIdle);
	this->mouseSpriteIdle->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->mouseSpritePoint = Sprite::create(Resources::GUI_MousePoint);
	this->mouseSpritePoint->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->currentMouseSprite = mouseSpriteIdle;

	this->addChild(this->mouseSpriteIdle);
}

Mouse::~Mouse()
{
}

void Mouse::SetCanClick(bool canClick)
{
	if (canClick)
	{
		this->currentMouseSprite = mouseSpritePoint;
	}
	else
	{
		this->currentMouseSprite = mouseSpriteIdle;
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
	this->currentMouseSprite->setPosition(Vec2(event->getCursorX(), event->getCursorY()));
}
