#include "SquallyMovementBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/Input.h"
#include "Engine/Maps/MapLayer.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Movement/EntityMovementBehavior.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string SquallyMovementBehavior::MapKey = "squally-movements";
const float SquallyMovementBehavior::SquallyMovementAcceleration = 9600.0f;

SquallyMovementBehavior* SquallyMovementBehavior::create(GameObject* owner)
{
	SquallyMovementBehavior* instance = new SquallyMovementBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyMovementBehavior::SquallyMovementBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);
	this->leftPressed = false;
	this->rightPressed = false;
	this->upPressed = false;
	this->downPressed = false;

	if (this->squally == nullptr)
	{
		this->invalidate();
	}

	this->isDisposing = false;
	this->isPositionSavingDisabled = false;
}

SquallyMovementBehavior::~SquallyMovementBehavior()
{
}

void SquallyMovementBehavior::onLoad()
{
	this->whenKeyPressedIgnorePause({ EventKeyboard::KeyCode::KEY_LEFT_ARROW, EventKeyboard::KeyCode::KEY_A }, [=](InputEvents::InputArgs* args)
	{
		this->leftPressed = true;
		this->onMovementChanged();
	});

	this->whenKeyPressedIgnorePause({ EventKeyboard::KeyCode::KEY_RIGHT_ARROW, EventKeyboard::KeyCode::KEY_D }, [=](InputEvents::InputArgs* args)
	{
		this->rightPressed = true;
		this->onMovementChanged();
	});

	this->whenKeyPressedIgnorePause({ EventKeyboard::KeyCode::KEY_UP_ARROW, EventKeyboard::KeyCode::KEY_W }, [=](InputEvents::InputArgs* args)
	{
		this->upPressed = true;
		this->onMovementChanged();
	});

	this->whenKeyPressedIgnorePause({ EventKeyboard::KeyCode::KEY_DOWN_ARROW, EventKeyboard::KeyCode::KEY_S }, [=](InputEvents::InputArgs* args)
	{
		this->downPressed = true;
		this->onMovementChanged();
	});

	this->whenKeyReleasedIgnorePause({ EventKeyboard::KeyCode::KEY_LEFT_ARROW, EventKeyboard::KeyCode::KEY_A }, [=](InputEvents::InputArgs* args)
	{
		this->leftPressed = false;
		this->onMovementChanged();
	});

	this->whenKeyReleasedIgnorePause({ EventKeyboard::KeyCode::KEY_RIGHT_ARROW, EventKeyboard::KeyCode::KEY_D }, [=](InputEvents::InputArgs* args)
	{
		this->rightPressed = false;
		this->onMovementChanged();
	});

	this->whenKeyReleasedIgnorePause({ EventKeyboard::KeyCode::KEY_UP_ARROW, EventKeyboard::KeyCode::KEY_W }, [=](InputEvents::InputArgs* args)
	{
		this->upPressed = false;
		this->onMovementChanged();
	});

	this->whenKeyReleasedIgnorePause({ EventKeyboard::KeyCode::KEY_DOWN_ARROW, EventKeyboard::KeyCode::KEY_S }, [=](InputEvents::InputArgs* args)
	{
		this->downPressed = false;
		this->onMovementChanged();
	});

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventBeforePlatformerMapChange, [=](EventCustom* eventCustom)
	{
		this->isDisposing = true;

		SaveManager::softDeleteProfileData(SaveKeys::SaveKeySquallyPositionX);
		SaveManager::softDeleteProfileData(SaveKeys::SaveKeySquallyPositionY);
		SaveManager::softDeleteProfileData(SaveKeys::SaveKeySquallyPositionZ);
		SaveManager::softDeleteProfileData(SaveKeys::SaveKeySquallyLayerId);
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventSavePosition, [=](EventCustom* eventCustom)
	{
		this->saveSquallyPosition();
	}));

	this->squally->watchForAttachedBehavior<EntityMovementBehavior>([=](EntityMovementBehavior* entityMovementBehavior)
	{
		entityMovementBehavior->setMoveAcceleration(SquallyMovementBehavior::SquallyMovementAcceleration);
	});

	if (!this->isPositionSavingDisabled)
	{
		this->loadSquallyPosition();
	}
	
	CameraTrackingData* trackingData = GameCamera::getInstance()->getCurrentTrackingData();
	Node* target = trackingData == nullptr ? nullptr : trackingData->target;

	if (target == this->squally)
	{
		GameCamera::getInstance()->setCameraPositionToTrackedTarget();
	}
	
	this->scheduleUpdate();
}

void SquallyMovementBehavior::onDisable()
{
	super::onDisable();
}

void SquallyMovementBehavior::update(float dt)
{
	// Soft save the player's position
	if (!this->isPositionSavingDisabled && !this->isDisposing)
	{
		if (this->squally->getRuntimeStateOrDefaultFloat(StateKeys::MovementX, 0.0f) != 0.0f ||
			this->squally->getRuntimeStateOrDefaultFloat(StateKeys::MovementY, 0.0f) != 0.0f)
		{
			this->saveSquallyPosition();
		}
	}
}

void SquallyMovementBehavior::onMovementChanged()
{
	bool isCinematicHijacked = this->squally->getRuntimeStateOrDefaultBool(StateKeys::CinematicHijacked, false);

	this->squally->setState(StateKeys::MovementX, Value((this->leftPressed ? -1.0f : 0.0f) + (this->rightPressed ? 1.0f : 0.0f)));
	this->squally->setState(StateKeys::MovementY, Value((this->downPressed ? -1.0f : 0.0f) + (this->upPressed ? 1.0f : 0.0f)));

	if (isCinematicHijacked)
	{
		return;
	}
}

void SquallyMovementBehavior::disablePositionSaving()
{
	this->isPositionSavingDisabled = true;
}

void SquallyMovementBehavior::saveSquallyPosition()
{
	Vec3 position = GameUtils::getWorldCoords3D(this->squally);
	MapLayer* mapLayer = GameUtils::getFirstParentOfType<MapLayer>(this->squally);
	std::string layerId = mapLayer == nullptr ? "" : mapLayer->getUniqueIdentifier();

	SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySquallyPositionX, Value(position.x));
	SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySquallyPositionY, Value(position.y));
	SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySquallyPositionZ, Value(position.z));
	SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySquallyLayerId, Value(layerId));
}

void SquallyMovementBehavior::loadSquallyPosition()
{
	Vec3 position = GameUtils::getWorldCoords3D(this->squally);

	float x = SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyPositionX, Value(position.x)).asFloat();
	float y = SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyPositionY, Value(position.y)).asFloat();
	float z = SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyPositionZ, Value(position.z)).asFloat();
	std::string layerId = SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyLayerId, Value("")).asString();

	GameUtils::setWorldCoords3D(this->squally, Vec3(x, y, z));

	if (!layerId.empty())
	{
		this->defer([=]()
		{
			ObjectEvents::QueryObjects<MapLayer>(QueryObjectsArgs<MapLayer>([&](MapLayer* mapLayer)
			{
				GameUtils::changeParent(this->squally, mapLayer, true);
			}), layerId);
		});
	}
}
