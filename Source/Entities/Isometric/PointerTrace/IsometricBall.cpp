#include "IsometricBall.h"

#include "Engine/Input/Input.h"
#include "Events/NavigationEvents.h"

#include "Resources/IsometricEntityResources.h"

using namespace cocos2d;

const std::string IsometricBall::KeyBallProperty = "ball";

IsometricBall* IsometricBall::deserialize(ValueMap& initProperties)
{
	return IsometricBall::create(initProperties);

	IsometricBall::instance = instance;
	instance->autorelease();

	return instance;
}

IsometricBall* IsometricBall::create(cocos2d::ValueMap& initProperties)
{
	IsometricBall* instance = new IsometricBall(initProperties);

	instance->autorelease();
	
	return instance;
}

IsometricBall::IsometricBall(ValueMap& initProperties) : super::IsometricEntity(initProperties,
	IsometricEntityResources::SquallBall_Animations,
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

IsometricBall::~IsometricBall()
{
}

void IsometricBall::onEnter()
{
	super::onEnter();
}

Vec2 IsometricBall::getButtonOffset()
{
	return Vec2(0, 72.0f);
}

void IsometricBall::update(float dt)
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
