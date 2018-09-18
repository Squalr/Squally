#include "InputManager.h"

InputManager* InputManager::inputManagerInstance = nullptr;

InputManager* InputManager::claimInstance()
{
	InputManager* inputManager = InputManager::getInstance();

	GameUtils::changeParent(inputManager, nullptr, false);

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
	this->pressedKeys = new std::unordered_map<int, bool>();
	this->pressedKeysPrevious = new std::unordered_map<int, bool>();
}

InputManager::~InputManager()
{
	delete(this->pressedKeys);
	delete(this->pressedKeysPrevious);
}

void InputManager::resume()
{
	// Anything could have happened to the key states while paused, best just to clear them
	this->pressedKeys->clear();

	Node::resume();
}

bool InputManager::isKeyJustPressed(EventKeyboard::KeyCode keyCode)
{
	if (this->pressedKeys->count((int)keyCode) > 0)
	{
		return pressedKeys->at((int)keyCode);
	}

	return false;
}

bool InputManager::isPressed(EventKeyboard::KeyCode keyCode)
{
	if (this->pressedKeys->count((int)keyCode) > 0)
	{
		return pressedKeys->at((int)keyCode);
	}

	return false;
}

bool InputManager::isReleased(EventKeyboard::KeyCode keyCode)
{
	if (this->pressedKeys->count((int)keyCode) > 0)
	{
		return !pressedKeys->at((int)keyCode);
	}

	return false;
}

void InputManager::initializeListeners()
{
	SmartNode::initializeListeners();

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(InputManager::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(InputManager::onKeyReleased, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void InputManager::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	this->pressedKeys->emplace((int)keyCode, true);
}

void InputManager::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	this->pressedKeys->emplace((int)keyCode, false);
}
