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
	this->squally = static_cast<Squally*>(owner);
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
	this->whenKeyPressedIgnorePause({ InputEvents::KeyCode::KEY_LEFT_ARROW, InputEvents::KeyCode::KEY_A }, [=](InputEvents::KeyboardEventArgs* args)
	{
		this->leftPressed = true;
		this->onMovementChanged();
	});

	this->whenKeyPressedIgnorePause({ InputEvents::KeyCode::KEY_RIGHT_ARROW, InputEvents::KeyCode::KEY_D }, [=](InputEvents::KeyboardEventArgs* args)
	{
		this->rightPressed = true;
		this->onMovementChanged();
	});

	this->whenKeyPressedIgnorePause({ InputEvents::KeyCode::KEY_UP_ARROW, InputEvents::KeyCode::KEY_W }, [=](InputEvents::KeyboardEventArgs* args)
	{
		this->upPressed = true;
		this->onMovementChanged();
	});

	this->whenKeyPressedIgnorePause({ InputEvents::KeyCode::KEY_DOWN_ARROW, InputEvents::KeyCode::KEY_S }, [=](InputEvents::KeyboardEventArgs* args)
	{
		this->downPressed = true;
		this->onMovementChanged();
	});

	this->whenKeyReleasedIgnorePause({ InputEvents::KeyCode::KEY_LEFT_ARROW, InputEvents::KeyCode::KEY_A }, [=](InputEvents::KeyboardEventArgs* args)
	{
		this->leftPressed = false;
		this->onMovementChanged();
	});

	this->whenKeyReleasedIgnorePause({ InputEvents::KeyCode::KEY_RIGHT_ARROW, InputEvents::KeyCode::KEY_D }, [=](InputEvents::KeyboardEventArgs* args)
	{
		this->rightPressed = false;
		this->onMovementChanged();
	});

	this->whenKeyReleasedIgnorePause({ InputEvents::KeyCode::KEY_UP_ARROW, InputEvents::KeyCode::KEY_W }, [=](InputEvents::KeyboardEventArgs* args)
	{
		this->upPressed = false;
		this->onMovementChanged();
	});

	this->whenKeyReleasedIgnorePause({ InputEvents::KeyCode::KEY_DOWN_ARROW, InputEvents::KeyCode::KEY_S }, [=](InputEvents::KeyboardEventArgs* args)
	{
		this->downPressed = false;
		this->onMovementChanged();
	});

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventBeforePlatformerMapChange, [=](EventCustom* eventCustom)
	{
		this->isDisposing = true;

		SaveManager::SoftDeleteProfileData(SaveKeys::SaveKeySquallyPositionX);
		SaveManager::SoftDeleteProfileData(SaveKeys::SaveKeySquallyPositionY);
		SaveManager::SoftDeleteProfileData(SaveKeys::SaveKeySquallyPositionZ);
		SaveManager::SoftDeleteProfileData(SaveKeys::SaveKeySquallyLayerId);
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
	this->squally->setState(StateKeys::MovementX, Value((this->leftPressed ? -1.0f : 0.0f) + (this->rightPressed ? 1.0f : 0.0f)));
	
	// We actually want to prioritize jump, instead of canceling out the inputs. This is better UX for performing a crouch jump.
	// this->squally->setState(StateKeys::MovementY, Value((this->downPressed ? -1.0f : 0.0f) + (this->upPressed ? 1.0f : 0.0f)));
	this->squally->setState(StateKeys::MovementY, Value((this->upPressed ? 1.0f : (this->downPressed ? -1.0f : 0.0f))));
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

	float x = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeySquallyPositionX, Value(position.x)).asFloat();
	float y = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeySquallyPositionY, Value(position.y)).asFloat();
	float z = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeySquallyPositionZ, Value(position.z)).asFloat();
	std::string layerId = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeySquallyLayerId, Value("")).asString();

	PlatformerEvents::TriggerWarpObjectToLocation(PlatformerEvents::WarpObjectToLocationArgs(this->squally, Vec3(x, y, z), true));

	if (!layerId.empty())
	{
		this->defer([=]()
		{
			ObjectEvents::QueryObjects<MapLayer>(QueryObjectsArgs<MapLayer>([&](MapLayer* mapLayer)
			{
				GameUtils::changeParent(this->squally, mapLayer, true);
			}), layerId);

			PlatformerEvents::TriggerSquallySpawned();
		});
	}
	else
	{
		PlatformerEvents::TriggerSquallySpawned();
	}
}
