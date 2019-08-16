#include "SquallyMovementBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Input/Input.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
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

	this->isDisposing = false;
	this->elapsed = 0.0f;
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

	this->movement = Vec2::ZERO;
	this->elapsed += dt;

	this->squally->getFloatNode()->setPositionY(std::sin(this->elapsed * 1.5f) * 8.0f);

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

	if (!this->isDisposing && this->movement != Vec2::ZERO)
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

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventBeforePlatformerMapChange, [=](EventCustom* eventCustom)
	{
		this->isDisposing = true;

		SaveManager::softDeleteProfileData(SaveKeys::SaveKeySquallyPositionX);
		SaveManager::softDeleteProfileData(SaveKeys::SaveKeySquallyPositionY);
	}));

	this->squally->setPosition(Vec2(
		SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyPositionX, Value(this->squally->getPositionX())).asFloat(),
		SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyPositionY, Value(this->squally->getPositionY())).asFloat()
	));
	
	CameraTrackingData* trackingData = GameCamera::getInstance()->getCurrentTrackingData();
	Node* target = trackingData == nullptr ? nullptr : trackingData->target;

	if (target == this->squally)
	{
		GameCamera::getInstance()->setCameraPositionToTrackedTarget();
	}
}
