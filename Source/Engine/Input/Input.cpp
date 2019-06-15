#include "Input.h"

#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Events/InputEvents.h"
#include "Engine/GlobalDirector.h"

using namespace cocos2d;

Input* Input::instance = nullptr;

void Input::registerGlobalNode()
{
	if (Input::instance == nullptr)
	{
		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(Input::getInstance());
	}
}

Input* Input::getInstance()
{
	if (Input::instance == nullptr)
	{
		Input::instance = new Input();

		Input::instance->autorelease();
	}

	return Input::instance;
}

Input::Input()
{
	this->pressedKeys = std::unordered_map<int, bool>();
	this->pressedKeysPrevious = std::unordered_map<int, bool>();
}

Input::~Input()
{
}

void Input::initializeListeners()
{
	super::initializeListeners();

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(Input::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Input::onKeyReleased, this);

	this->addGlobalEventListener(keyboardListener);
}

void Input::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	this->pressedKeysPrevious = this->pressedKeys;
	this->pressedKeys[(int)keyCode] = true;

	// Check if previously not pressed or if previously up
	if (Input::getInstance()->pressedKeysPrevious.find((int)keyCode) == Input::getInstance()->pressedKeysPrevious.end() ||
		!Input::getInstance()->pressedKeysPrevious[(int)keyCode])
	{
		InputEvents::TriggerKeyJustPressed(InputEvents::InputArgs(keyCode));
	}
}

void Input::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	this->pressedKeysPrevious = this->pressedKeys;
	this->pressedKeys[(int)keyCode] = false;

	InputEvents::TriggerKeyJustReleased(InputEvents::InputArgs(keyCode));
}

EventKeyboard::KeyCode Input::getActiveModifiers()
{
	EventKeyboard::KeyCode modifiers = EventKeyboard::KeyCode::KEY_NONE;

	if (Input::isPressed(EventKeyboard::KeyCode::KEY_ALT))
	{
		modifiers = (EventKeyboard::KeyCode)((int)modifiers | (int)EventKeyboard::KeyCode::KEY_ALT);
	}

	if (Input::isPressed(EventKeyboard::KeyCode::KEY_CTRL))
	{
		modifiers = (EventKeyboard::KeyCode)((int)modifiers | (int)EventKeyboard::KeyCode::KEY_CTRL);
	}

	return modifiers;
}

bool Input::isPressed(EventKeyboard::KeyCode keyCode)
{
	if (Input::getInstance()->pressedKeys.find((int)keyCode) != Input::getInstance()->pressedKeys.end())
	{
		return Input::getInstance()->pressedKeys[(int)keyCode];
	}

	return false;
}

bool Input::isReleased(EventKeyboard::KeyCode keyCode)
{
	if (Input::getInstance()->pressedKeys.find((int)keyCode) != Input::getInstance()->pressedKeys.end())
	{
		return !Input::getInstance()->pressedKeys[(int)keyCode];
	}

	return true;
}
