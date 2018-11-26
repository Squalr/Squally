#include "IsometricSqually.h"

IsometricSqually* IsometricSqually::squallyInstance = nullptr;
const std::string IsometricSqually::KeySquallyProperty = "squally";

IsometricSqually* IsometricSqually::deserialize(ValueMap* initProperties)
{
	IsometricSqually* instance = new IsometricSqually(initProperties);

	IsometricSqually::squallyInstance = instance;
	instance->autorelease();

	return instance;
}

IsometricSqually* IsometricSqually::getInstance()
{
	return IsometricSqually::squallyInstance;
}

IsometricSqually::IsometricSqually(ValueMap* initProperties) : IsometricEntity::IsometricEntity(initProperties,
	EntityResources::Isometric_Squally_Animations,
	1.0f,
	Vec2(-128.0f, 0.0f))
{
	this->registerHackables();
}

IsometricSqually::~IsometricSqually()
{
}

void IsometricSqually::onEnter()
{
	IsometricEntity::onEnter();

	this->inputManager = InputManager::getInstance();
}

void IsometricSqually::registerHackables()
{
}

Vec2 IsometricSqually::getButtonOffset()
{
	return Vec2(0, 72.0f);
}

void IsometricSqually::update(float dt)
{
	IsometricEntity::update(dt);

	this->movement.x = 0.0f;
	this->movement.y = 0.0f;

	if (this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) || this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_A))
	{
		this->movement.x -= 1.0f;
	}

	if (this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) || this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_D))
	{
		this->movement.x += 1.0f;
	}

	if (this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_UP_ARROW) || this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_W) || this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_SPACE))
	{
		this->movement.y += 1.0f;
	}

	if (this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW) || this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_S))
	{
		this->movement.y -= 1.0f;
	}
}
