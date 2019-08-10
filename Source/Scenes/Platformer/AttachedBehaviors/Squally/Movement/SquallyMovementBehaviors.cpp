#include "SquallyMovementBehaviors.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/Input.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string SquallyMovementBehaviors::MapKeyAttachedBehavior = "squally-movements";

SquallyMovementBehaviors* SquallyMovementBehaviors::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	SquallyMovementBehaviors* instance = new SquallyMovementBehaviors(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

SquallyMovementBehaviors::SquallyMovementBehaviors(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->squally = static_cast<Squally*>(owner);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}
}

SquallyMovementBehaviors::~SquallyMovementBehaviors()
{
}

void SquallyMovementBehaviors::update(float dt)
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

void SquallyMovementBehaviors::onLoad()
{
	this->scheduleUpdate();
}
