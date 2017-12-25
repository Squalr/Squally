#include "InputManager.h"

InputManager* InputManager::inputManagerInstance = nullptr;

InputManager* InputManager::ClaimInstance()
{
	InputManager* mouse = InputManager::GetInstance();

	// Free the mouse from it's parent
	if (mouse->getParent() != nullptr)
	{
		mouse->getParent()->removeChild(InputManager::inputManagerInstance);
	}

	return InputManager::inputManagerInstance;
}

InputManager* InputManager::GetInstance()
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

bool InputManager::IsKeyJustPressed(EventKeyboard::KeyCode keyCode)
{
	if (this->pressedKeys->count(keyCode) > 0)
	{
		return pressedKeys->at(keyCode);
	}

	return false;
}

bool InputManager::IsPressed(EventKeyboard::KeyCode keyCode)
{
	if (this->pressedKeys->count(keyCode) > 0)
	{
		return pressedKeys->at(keyCode);
	}

	return false;
}

bool InputManager::IsReleased(EventKeyboard::KeyCode keyCode)
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

	listener->onKeyPressed = CC_CALLBACK_2(InputManager::OnKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(InputManager::OnKeyReleased, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void InputManager::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	pressedKeys->insert_or_assign(keyCode, true);
}

void InputManager::OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	pressedKeys->insert_or_assign(keyCode, false);
}
