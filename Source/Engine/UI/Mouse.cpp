#include "Mouse.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/MouseEvents.h"
#include "Engine/Input/MouseState.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

Mouse* Mouse::create()
{
	Mouse* instance = new Mouse();
	
	instance->autorelease();

	return instance;
}

Mouse::Mouse()
{
	this->mouseSpriteIdle = Sprite::create(UIResources::Menus_MouseIdle);
	this->mouseSpritePoint = Sprite::create(UIResources::Menus_MousePoint);
	this->mouseSpritePointPressed = Sprite::create(UIResources::Menus_MousePointPressed);
	this->mouseSpriteDrag = Sprite::create(UIResources::Menus_MouseDrag);

	// Anchor point is the top left for the mouse -- this is where the click happens
	this->mouseSpriteIdle->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->mouseSpritePoint->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->mouseSpritePointPressed->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->mouseSpriteDrag->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->setActiveMouseSprite(this->mouseSpriteIdle);

	this->addChild(this->mouseSpriteIdle);
	this->addChild(this->mouseSpritePoint);
	this->addChild(this->mouseSpritePointPressed);
	this->addChild(this->mouseSpriteDrag);
}

Mouse::~Mouse()
{
}

void Mouse::onEnter()
{
	SmartNode::onEnter();

	this->setSpriteToCursorPosition();
	this->setActiveMouseSprite(this->mouseSpriteIdle);
}

void Mouse::initializeListeners()
{
	SmartNode::initializeListeners();

	EventListenerCustom* mouseStateUpdateListener = EventListenerCustom::create(
		MouseEvents::MouseStateUpdateEvent,
		CC_CALLBACK_1(Mouse::onMouseStateUpdateEvent, this)
	);

	this->addEventListener(mouseStateUpdateListener);
}

void Mouse::pause()
{
	this->setVisible(false);

	SmartNode::pause();
}

void Mouse::resume()
{
	this->setSpriteToCursorPosition();
	this->setVisible(true);

	SmartNode::resume();
}

const cocos2d::Vec2& Mouse::getPosition() const
{
	return this->readMousePosition;
}

void Mouse::onMouseStateUpdateEvent(EventCustom* eventCustom)
{
	MouseEvents::MouseEventArgs* args = (MouseEvents::MouseEventArgs*)(eventCustom->getUserData());

	if (args->isDragging)
	{
		this->setActiveMouseSprite(this->mouseSpriteDrag);
	}
	else if (args->isLeftClicked && args->canClick)
	{
		this->setActiveMouseSprite(this->mouseSpritePointPressed);
	}
	else if (args->canClick)
	{
		this->setActiveMouseSprite(this->mouseSpritePoint);
	}
	else
	{
		this->setActiveMouseSprite(this->mouseSpriteIdle);
	}

	this->readMousePosition = MouseState::getMousePosition();
	this->setSpriteToCursorPosition();
}

void Mouse::setActiveMouseSprite(Sprite* mouseSprite)
{
	this->mouseSpriteIdle->setVisible(false);
	this->mouseSpritePoint->setVisible(false);
	this->mouseSpritePointPressed->setVisible(false);
	this->mouseSpriteDrag->setVisible(false);

	// This will be one of the ones above
	mouseSprite->setVisible(true);
}

void Mouse::setSpriteToCursorPosition()
{
	this->mouseSpriteIdle->setPosition(MouseState::getMousePosition());
	this->mouseSpritePoint->setPosition(MouseState::getMousePosition());
	this->mouseSpritePointPressed->setPosition(MouseState::getMousePosition());
	this->mouseSpriteDrag->setPosition(MouseState::getMousePosition());
}
