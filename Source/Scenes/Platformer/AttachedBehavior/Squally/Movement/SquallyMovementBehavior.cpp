#include "SquallyMovementBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Input/Input.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

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

	this->isDisposing = false;
}

SquallyMovementBehavior::~SquallyMovementBehavior()
{
}

void SquallyMovementBehavior::update(float dt)
{
	if (this->squally == nullptr)
	{
		return;
	}

	Vec2 movement = Vec2::ZERO;

	if (Input::isPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) || Input::isPressed(EventKeyboard::KeyCode::KEY_A))
	{
		this->squally->setState(StateKeys::MovementX, Value(this->squally->getStateOrDefaultFloat(StateKeys::MovementX, 0.0f) - 1.0f));
	}

	if (Input::isPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) || Input::isPressed(EventKeyboard::KeyCode::KEY_D))
	{
		this->squally->setState(StateKeys::MovementX, Value(this->squally->getStateOrDefaultFloat(StateKeys::MovementX, 0.0f) + 1.0f));
	}

	if (Input::isPressed(EventKeyboard::KeyCode::KEY_UP_ARROW) || Input::isPressed(EventKeyboard::KeyCode::KEY_W))
	{
		this->squally->setState(StateKeys::MovementY, Value(this->squally->getStateOrDefaultFloat(StateKeys::MovementY, 0.0f) + 1.0f));
	}

	if (Input::isPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW) || Input::isPressed(EventKeyboard::KeyCode::KEY_S))
	{
		this->squally->setState(StateKeys::MovementY, Value(this->squally->getStateOrDefaultFloat(StateKeys::MovementY, 0.0f) - 1.0f));
	}

	// Soft save the player's position
	if (!this->isDisposing)
	{
		if (this->squally->getStateOrDefaultFloat(StateKeys::MovementX, 0.0f) != 0.0f ||
			this->squally->getStateOrDefaultFloat(StateKeys::MovementY, 0.0f) != 0.0f)
		{
			Vec2 position = GameUtils::getWorldCoords(this->squally);
			SaveManager::softSaveProfileData(SaveKeys::SaveKeySquallyPositionX, Value(position.x));
			SaveManager::softSaveProfileData(SaveKeys::SaveKeySquallyPositionY, Value(position.y));
		}
	}

	super::update(dt);
}

void SquallyMovementBehavior::onLoad()
{
	this->scheduleUpdate();

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventBeforePlatformerMapChange, [=](EventCustom* eventCustom)
	{
		this->isDisposing = true;

		SaveManager::softDeleteProfileData(SaveKeys::SaveKeySquallyPositionX);
		SaveManager::softDeleteProfileData(SaveKeys::SaveKeySquallyPositionY);
	}));

	Vec2 position = GameUtils::getWorldCoords(this->squally);

	this->squally->setPosition(Vec2(
		SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyPositionX, Value(position.x)).asFloat(),
		SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyPositionY, Value(position.y)).asFloat()
	));
	
	CameraTrackingData* trackingData = GameCamera::getInstance()->getCurrentTrackingData();
	Node* target = trackingData == nullptr ? nullptr : trackingData->target;

	if (target == this->squally)
	{
		GameCamera::getInstance()->setCameraPositionToTrackedTarget();
	}
}
