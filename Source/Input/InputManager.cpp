#include "InputManager.h"

InputManager* InputManager::inputManagerInstance = nullptr;

InputManager* InputManager::claimInstance()
{
	InputManager* mouse = InputManager::getInstance();

	// Free the input manager from it's parent
	if (mouse->getParent() != nullptr)
	{
		mouse->getParent()->removeChild(InputManager::inputManagerInstance);
	}

	return InputManager::inputManagerInstance;
}

InputManager* InputManager::getInstance()
{
	if (InputManager::inputManagerInstance == nullptr)
	{
		InputManager::inputManagerInstance = new InputManager();
	}

	return InputManager::inputManagerInstance;
}

InputManager::InputManager()
{
	this->pressedKeys = new std::unordered_map<EventKeyboard::KeyCode, bool>();
	this->pressedKeysPrevious = new std::unordered_map<EventKeyboard::KeyCode, bool>();

	this->InitializeListeners();
	this->scheduleUpdate();
}

InputManager::~InputManager()
{
}

bool InputManager::isKeyJustPressed(EventKeyboard::KeyCode keyCode)
{
	if (this->pressedKeys->count(keyCode) > 0)
	{
		return pressedKeys->at(keyCode);
	}

	return false;
}

bool InputManager::isPressed(EventKeyboard::KeyCode keyCode)
{
	if (this->pressedKeys->count(keyCode) > 0)
	{
		return pressedKeys->at(keyCode);
	}

	return false;
}

bool InputManager::isReleased(EventKeyboard::KeyCode keyCode)
{
	if (this->pressedKeys->count(keyCode) > 0)
	{
		return !pressedKeys->at(keyCode);
	}

	return false;
}

void InputManager::update(float dt)
{
	Node::update(dt);
}

void InputManager::InitializeListeners()
{
	EventListenerKeyboard* listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(InputManager::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(InputManager::onKeyReleased, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void InputManager::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	pressedKeys->insert_or_assign(keyCode, true);
}

void InputManager::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	pressedKeys->insert_or_assign(keyCode, false);
}
