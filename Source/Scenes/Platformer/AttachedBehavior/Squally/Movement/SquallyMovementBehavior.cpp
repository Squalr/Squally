#include "SquallyMovementBehavior.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/Input.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string SquallyMovementBehavior::MapKeyAttachedBehavior = "squally-movements";

SquallyMovementBehavior* SquallyMovementBehavior::create(GameObject* owner)
{
	SquallyMovementBehavior* instance = new SquallyMovementBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyMovementBehavior::SquallyMovementBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}
}

SquallyMovementBehavior::~SquallyMovementBehavior()
{
}

void SquallyMovementBehavior::update(float dt)
{
	//// Vec2 squallyPosition = GameUtils::getScreenBounds(this->squally->animationNode).origin;
	//// this->squally->animationNode->setFlippedX(squallyPosition.x > MouseState::getMousePosition().x);

	this->movement = Vec2::ZERO;

	if (Input::isPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) || Input::isPressed(EventKeyboard::KeyCode::KEY_A))
	{
		this->movement.x = -1.0f;
	}

	if (Input::isPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) || Input::isPressed(EventKeyboard::KeyCode::KEY_D))
	{
		this->movement.x = 1.0f;
	}

	if (Input::isPressed(EventKeyboard::KeyCode::KEY_UP_ARROW) || Input::isPressed(EventKeyboard::KeyCode::KEY_W))
	{
		this->movement.y = 1.0f;
	}

	if (Input::isPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW) || Input::isPressed(EventKeyboard::KeyCode::KEY_S))
	{
		this->movement.y = -1.0f;
	}

	if (this->movement != Vec2::ZERO)
	{
		// Soft save the player's position
		SaveManager::softSaveProfileData(SaveKeys::SaveKeySquallyPositionX, Value(this->squally->getPositionX()));
		SaveManager::softSaveProfileData(SaveKeys::SaveKeySquallyPositionY, Value(this->squally->getPositionY()));
	}

	super::update(dt);
}

void SquallyMovementBehavior::onLoad()
{
	this->scheduleUpdate();
}
