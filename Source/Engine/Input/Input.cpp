#include "Input.h"

#include "cocos/base/CCEventListenerKeyboard.h"

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
	GlobalNode::initializeListeners();

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(Input::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Input::onKeyReleased, this);

	this->addEventListener(keyboardListener);
}

void Input::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	this->pressedKeys[(int)keyCode] = true;
}

void Input::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	this->pressedKeys[(int)keyCode] = false;
}

bool Input::isKeyJustPressed(EventKeyboard::KeyCode keyCode)
{
	if (Input::getInstance()->pressedKeys.find((int)keyCode) != Input::getInstance()->pressedKeys.end())
	{
		return Input::getInstance()->pressedKeys.at((int)keyCode);
	}

	return false;
}

bool Input::isPressed(EventKeyboard::KeyCode keyCode)
{
	if (Input::getInstance()->pressedKeys.find((int)keyCode) != Input::getInstance()->pressedKeys.end())
	{
		return Input::getInstance()->pressedKeys.at((int)keyCode);
	}

	return false;
}

bool Input::isReleased(EventKeyboard::KeyCode keyCode)
{
	if (Input::getInstance()->pressedKeys.find((int)keyCode) != Input::getInstance()->pressedKeys.end())
	{
		return !Input::getInstance()->pressedKeys.at((int)keyCode);
	}

	return true;
}
