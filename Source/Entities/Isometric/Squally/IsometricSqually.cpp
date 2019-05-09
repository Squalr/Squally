#include "IsometricSqually.h"

#include "Engine/Input/Input.h"
#include "Events/NavigationEvents.h"

#include "Resources/IsometricEntityResources.h"

using namespace cocos2d;

IsometricSqually* IsometricSqually::squallyInstance = nullptr;
const std::string IsometricSqually::KeySquallyProperty = "squally";

IsometricSqually* IsometricSqually::deserialize(ValueMap& initProperties)
{
	return IsometricSqually::create(initProperties);
}

IsometricSqually* IsometricSqually::create(cocos2d::ValueMap& initProperties)
{
	IsometricSqually* instance = new IsometricSqually(initProperties);

	instance->autorelease();

	return instance;
}

IsometricSqually::IsometricSqually(ValueMap& initProperties) : super::IsometricEntity(initProperties,
	IsometricEntityResources::Squally_Animations,
	1.0f,
	Vec2(-128.0f, 0.0f))
{
}

IsometricSqually::~IsometricSqually()
{
}

void IsometricSqually::onEnter()
{
	super::onEnter();
}

Vec2 IsometricSqually::getButtonOffset()
{
	return Vec2(0, 72.0f);
}

void IsometricSqually::update(float dt)
{
	super::update(dt);

	this->movement.x = 0.0f;
	this->movement.y = 0.0f;

	if (Input::isPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) || Input::isPressed(EventKeyboard::KeyCode::KEY_A))
	{
		this->movement.x -= 1.0f;
	}

	if (Input::isPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) || Input::isPressed(EventKeyboard::KeyCode::KEY_D))
	{
		this->movement.x += 1.0f;
	}

	if (Input::isPressed(EventKeyboard::KeyCode::KEY_UP_ARROW) || Input::isPressed(EventKeyboard::KeyCode::KEY_W) || Input::isPressed(EventKeyboard::KeyCode::KEY_SPACE))
	{
		this->movement.y += 1.0f;
	}

	if (Input::isPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW) || Input::isPressed(EventKeyboard::KeyCode::KEY_S))
	{
		this->movement.y -= 1.0f;
	}
}
