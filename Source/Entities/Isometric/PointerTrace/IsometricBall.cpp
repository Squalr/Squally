#include "IsometricBall.h"

#include "Engine/Input/Input.h"
#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricEntityResources.h"

using namespace cocos2d;

const std::string IsometricBall::MapKey = "ball";
const float IsometricBall::MovementSpeed = 0.2f;

IsometricBall* IsometricBall::deserialize(ValueMap& properties)
{
	IsometricBall* instance = new IsometricBall(properties);

	instance->autorelease();
	
	return instance;
}

IsometricBall::IsometricBall(ValueMap& properties) : super(properties,
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

	this->scheduleUpdate();
}

void IsometricBall::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	RegisterState::setRegisterEip(this->getGridIndex());
}

void IsometricBall::update(float dt)
{
	super::update(dt);

	if (Input::isPressed(InputEvents::KeyCode::KEY_LEFT_ARROW) || Input::isPressed(InputEvents::KeyCode::KEY_A))
	{
		this->moveUp(IsometricBall::MovementSpeed);
	}
	else if (Input::isPressed(InputEvents::KeyCode::KEY_RIGHT_ARROW) || Input::isPressed(InputEvents::KeyCode::KEY_D))
	{
		this->moveDown(IsometricBall::MovementSpeed);
	}
	else if (Input::isPressed(InputEvents::KeyCode::KEY_UP_ARROW) || Input::isPressed(InputEvents::KeyCode::KEY_W) || Input::isPressed(InputEvents::KeyCode::KEY_SPACE))
	{
		this->moveRight(IsometricBall::MovementSpeed);
	}
	else if (Input::isPressed(InputEvents::KeyCode::KEY_DOWN_ARROW) || Input::isPressed(InputEvents::KeyCode::KEY_S))
	{
		this->moveLeft(IsometricBall::MovementSpeed);
	}
}
