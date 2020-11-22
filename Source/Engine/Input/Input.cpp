#include "Input.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCInputEvents.h"
#include "cocos/base/CCEventListenerCustom.h"

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
	
	/*
	EventListenerCustom* keyEvents = EventListenerCustom::create(KeyboardEvents::EventKeyboard, [=](EventCustom* eventCustom)
	{
		InputEvents::KeyboardArgs* args = static_cast<KeyboardEvents::KeyboardArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			if (args->isPressed)
			{
				this->onKeyPressed(args->keyCode, eventCustom);
			}
			else
			{
				this->onKeyReleased(args->keyCode, eventCustom);
			}
		}
	});

	this->addGlobalEventListener(keyEvents);
	*/
}

void Input::onKeyPressed(InputEvents::KeyCode keyCode, Event* event)
{
	this->pressedKeysPrevious = this->pressedKeys;
	this->pressedKeys[(int)keyCode] = true;

	// Check if previously not pressed or if previously up
	if (Input::getInstance()->pressedKeysPrevious.find((int)keyCode) == Input::getInstance()->pressedKeysPrevious.end() ||
		!Input::getInstance()->pressedKeysPrevious[(int)keyCode])
	{
		InputEvents::TriggerKeyJustPressed(InputEvents::KeyboardEventArgs(keyCode));
	}
}

void Input::onKeyReleased(InputEvents::KeyCode keyCode, Event* event)
{
	this->pressedKeysPrevious = this->pressedKeys;
	this->pressedKeys[(int)keyCode] = false;

	InputEvents::TriggerKeyJustReleased(InputEvents::KeyboardEventArgs(keyCode));
}

InputEvents::KeyCode Input::getActiveModifiers()
{
	InputEvents::KeyCode modifiers = InputEvents::KeyCode::KEY_NONE;

	if (Input::isPressed(InputEvents::KeyCode::KEY_SHIFT))
	{
		modifiers = (InputEvents::KeyCode)((int)modifiers | (int)InputEvents::KeyCode::KEY_SHIFT);
	}

	if (Input::isPressed(InputEvents::KeyCode::KEY_ALT))
	{
		modifiers = (InputEvents::KeyCode)((int)modifiers | (int)InputEvents::KeyCode::KEY_ALT);
	}

	if (Input::isPressed(InputEvents::KeyCode::KEY_CTRL))
	{
		modifiers = (InputEvents::KeyCode)((int)modifiers | (int)InputEvents::KeyCode::KEY_CTRL);
	}

	return modifiers;
}

bool Input::isPressed(InputEvents::KeyCode keyCode)
{
	if (Input::getInstance()->pressedKeys.find((int)keyCode) != Input::getInstance()->pressedKeys.end())
	{
		return Input::getInstance()->pressedKeys[(int)keyCode];
	}

	return false;
}

bool Input::isReleased(InputEvents::KeyCode keyCode)
{
	if (Input::getInstance()->pressedKeys.find((int)keyCode) != Input::getInstance()->pressedKeys.end())
	{
		return !Input::getInstance()->pressedKeys[(int)keyCode];
	}

	return true;
}
